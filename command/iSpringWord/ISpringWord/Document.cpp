#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "DeleteCommand.h"
#include "AddImageCommand.h"
#include "AddParagraphCommand.h"
#include "Paragraph.h"

using namespace std;

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	return m_items.at(index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	return m_items.at(index);
}

void CDocument::Save(const std::string& path) const
{
	SaveCommand saver(path);
	saver.SetTitle(m_title);
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		saver.AddItem(GetItem(i));
	}

	saver.Serialize();
}

void CDocument::Delete(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteCommand>(m_items, index));
}

std::shared_ptr<IImage> CDocument::InsertImage(const boost::filesystem::path& path, int width, int height, boost::optional<size_t> position)
{
	m_history.AddAndExecuteCommand(std::make_unique<CAddImageCommand>(m_history, m_items, path, width, height, "images", position));

	size_t index = m_items.size() - 1;
	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetImage();
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(m_history, text);
	m_history.AddAndExecuteCommand(std::make_unique<CAddParagraphCommand>(paragraph, m_items, position));

	size_t index = m_items.size() - 1;
	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetParagraph();
}

CDocument::~CDocument()
{

	boost::system::error_code errorCode;
	boost::filesystem::remove_all(boost::filesystem::path("images"), errorCode);
	if (errorCode)
	{
		std::cout << errorCode.message() << std::endl;
	}
}