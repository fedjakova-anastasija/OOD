#include "../ISpringWord/stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "DeleteCommand.h"
#include "AddImageCommand.h"
#include "AddParagraphCommand.h"
#include "Paragraph.h"
#include "SaveCommand.h"

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_title, title));
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
	//if (!boost::filesystem::exists(path))
	//{
	//	boost::filesystem::create_directory(path);
	//}
	saver.SetTitle(m_title);
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		saver.AddItem(GetItem(i));
	}

	saver.Save();
}

void CDocument::Delete(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("Wrong index!");
	}
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteCommand>(m_items, index));
}

std::shared_ptr<IImage> CDocument::InsertImage(const boost::filesystem::path& path, int width, int height, boost::optional<size_t> position)
{
	m_history.AddAndExecuteCommand(std::make_unique<CAddImageCommand>(m_history, m_items, path, width, height, "images", position));
	size_t index = (position != boost::none) ? position.get() : m_items.size() - 1;

	return m_items.at(index).GetImage();
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(m_history, text);
	m_history.AddAndExecuteCommand(std::make_unique<CAddParagraphCommand>(paragraph, m_items, position));
	size_t index = (position != boost::none) ? position.get() : m_items.size() - 1;

	return m_items.at(index).GetParagraph();
}

CDocument::~CDocument()
{
}