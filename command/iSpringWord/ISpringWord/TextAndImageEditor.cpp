#include "stdafx.h"
#include "TextAndImageEditor.h"
#include "Document.h"
#include "Menu.h"
#include "SaveCommand.h"

CTextAndImageEditor::CTextAndImageEditor() //-V730
	: m_document(std::make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](std::istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "<new title>", &CTextAndImageEditor::SetTitle);
	m_menu.AddItem("list", "Show document", bind(&CTextAndImageEditor::List, this, std::placeholders::_1));
	AddMenuItem("undo", "Undo command", &CTextAndImageEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CTextAndImageEditor::Redo);
	AddMenuItem("insertParagraph", "Insert Paragraph <position>|end <text>", &CTextAndImageEditor::InsertParagraph);
	AddMenuItem("save", "<path>", &CTextAndImageEditor::Save);
	AddMenuItem("replaceText", "<position> <text>", &CTextAndImageEditor::ReplaceText);
	AddMenuItem("deleteItem", "<position>", &CTextAndImageEditor::DeleteItem);
	AddMenuItem("insertImage", "<position>|end <width> <height> <path>", &CTextAndImageEditor::InsertImage);
	AddMenuItem("resizeImage", "<position>|end <width> <height>", &CTextAndImageEditor::ResizeImage);
}

void CTextAndImageEditor::Start()
{
	m_menu.Run();
}

void CTextAndImageEditor::AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
}

void CTextAndImageEditor::SetTitle(std::istream& in)
{
	std::string head;
	std::string tail;
	if (in >> head)
	{
		std::getline(in, tail);
	}
	std::string title = head + tail;
	m_document->SetTitle(title);
}

void CTextAndImageEditor::InsertParagraph(std::istream& input)
{
	std::string text;
	std::string position;

	if ((input >> position) && std::getline(input, text))
	{
		boost::optional<size_t> index = boost::none;
		if (position != "end")
		{
			index.emplace(stoi(position));
		}
		boost::algorithm::trim_left(text);
		m_document->InsertParagraph(text, index);
	}
	else
	{
		throw std::invalid_argument("<position>|end <text>");
	}
}

void CTextAndImageEditor::InsertImage(std::istream& input)
{
	std::string path;
	std::string position;
	int width = 0;
	int height = 0;

	if ((input >> position) && (input >> width) && (input >> height) && (std::getline(input, path)))
	{
		boost::optional<size_t> index = boost::none;
		if (position != "end")
		{
			index.emplace(stoi(position));
		}
		boost::algorithm::trim_left(path);
		m_document->InsertImage(boost::filesystem::path(path), width, height, index);
	}
	else
	{
		throw std::invalid_argument("<position>|end <width> <height> <path>");
	}
}

void CTextAndImageEditor::ReplaceText(std::istream& input)
{
	size_t index;
	std::string text;

	if ((input >> index) && std::getline(input, text))
	{
		auto paragraph = m_document->GetItem(index).GetParagraph();

		if (!paragraph)
		{
			throw std::logic_error("Wrong paragraph!");
		}

		boost::algorithm::trim_left(text);
		paragraph->SetText(text);
	}
	else
	{
		throw std::invalid_argument("<position> <text>");
	}
}

void CTextAndImageEditor::DeleteItem(std::istream& input)
{
	size_t index;
	if (input >> index)
	{
		m_document->Delete(index);
	}
	else
	{
		throw std::invalid_argument("<position>");
	}
}

void CTextAndImageEditor::List(std::istream&)
{
	std::cout << "-------------" << std::endl;
	std::cout << "Title: " << m_document->GetTitle() << std::endl;
	auto itemsCount = m_document->GetItemsCount();

	for (size_t i = 0; i < itemsCount; ++i)
	{
		std::cout << i << ". ";
		auto item = m_document->GetItem(i);

		if (auto paragraph = item.GetParagraph())
		{
			std::cout << "Paragraph: " << paragraph->GetText() << std::endl;
		}

		if (auto image = item.GetImage())
		{
			std::cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << std::endl;
		}
	}
	std::cout << "-------------" << std::endl;
}

void CTextAndImageEditor::ResizeImage(std::istream& input)
{
	size_t index;
	int width = 0;
	int height = 0;

	if ((input >> index) && (input >> width) && (input >> height))
	{
		auto image = m_document->GetItem(index).GetImage();
		if (!image)
		{
			throw std::logic_error("Wrong image!");
		}
		image->Resize(width, height);
	}
	else
	{
		throw std::invalid_argument("<position> <width> <height>");
	}
}

void CTextAndImageEditor::Undo(std::istream&)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		std::cout << "Can't undo" << std::endl;
	}
}

void CTextAndImageEditor::Redo(std::istream&)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		std::cout << "Can't redo" << std::endl;
	}
}

void CTextAndImageEditor::Save(std::istream& input)
{
	std::string path;
	std::getline(input, path);
	boost::algorithm::trim_left(path);
	m_document->Save(path);
}
