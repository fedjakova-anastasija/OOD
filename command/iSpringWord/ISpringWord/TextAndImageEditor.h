#pragma once
#include "IDocument.h"
#include "Menu.h"
#include <functional>

class CTextAndImageEditor
{
public:
	CTextAndImageEditor();
	void Start();

private:
	typedef void (CTextAndImageEditor::*MenuHandler)(std::istream& in);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);

	void SetTitle(std::istream&);
	void List(std::istream&);

	void Undo(std::istream&);
	void Redo(std::istream&);

	void ReplaceText(std::istream&);
	void InsertImage(std::istream&);
	void ResizeImage(std::istream&);

	void InsertParagraph(std::istream&);
	void Save(std::istream&);
	void DeleteItem(std::istream&);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};
