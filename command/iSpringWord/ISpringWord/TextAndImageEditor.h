#pragma once
#include "IDocument.h"
#include <functional>

class CTextAndImageEditor
{
public:
	CTextAndImageEditor();
	void Run();

private:
	using Command = std::function<void(std::istream& args)>;

	std::unique_ptr<IDocument> m_document;

	void AddParagraph(std::istream&);
	void AddImage(std::istream&);
	void SetTitle(std::istream&);

	void ReplaceText(std::istream&);
	void ResizeImage(std::istream&);
	void Delete(std::istream&);
	void Save(std::istream&);

	void Redo(std::istream&);
	void Undo(std::istream&);
	void List(std::istream&);
	void Help(std::istream&);

	struct EditorCommand
	{
		EditorCommand(const std::string& name, const std::string& description, const Command& command)
			: name(name)
			, description(description)
			, command(command)
		{
		}

		std::string name;
		std::string description;
		Command command;
	};
	std::vector<EditorCommand> EDITOR_COMMANDS = {
		{ "InsertParagraph", "Insert paragraph. Arguments: <position> | end <text>", std::bind(&CTextAndImageEditor::AddParagraph, this, std::placeholders::_1) },
		{ "InsertImage", "Insert Image. Arguments: <position> | end <width> <height> <path>", std::bind(&CTextAndImageEditor::AddImage, this, std::placeholders::_1) },
		{ "SetTitle", "Changes title. Arguments: <title>", std::bind(&CTextAndImageEditor::SetTitle, this, std::placeholders::_1) },
		{ "ReplaceText", "Replace text of paragraph at position. Arguments: <position> <text>", std::bind(&CTextAndImageEditor::ReplaceText, this, std::placeholders::_1) },
		{ "ResizeImage", "Resize image at position. Arguments: <position> <width> <height>", std::bind(&CTextAndImageEditor::ResizeImage, this, std::placeholders::_1) },
		{ "DeleteItem", "Delete item at position. Arguments: <position>", std::bind(&CTextAndImageEditor::Delete, this, std::placeholders::_1) },
		{ "Save", "Save document. Arguments: <path>", std::bind(&CTextAndImageEditor::Save, this, std::placeholders::_1) },
		{ "Redo", "Redo undone command.", std::bind(&CTextAndImageEditor::Redo, this, std::placeholders::_1) },
		{ "Undo", "Undo command.", std::bind(&CTextAndImageEditor::Undo, this, std::placeholders::_1) },
		{ "List", "Show document.", std::bind(&CTextAndImageEditor::List, this, std::placeholders::_1) },
		{ "Help", "Help.", std::bind(&CTextAndImageEditor::Help, this, std::placeholders::_1) }
	};
};
