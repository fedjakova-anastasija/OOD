#include "pch.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/AddParagraphCommand.h"
#include "../ISpringWord/Paragraph.h"

TEST_CASE("Can add and execute command")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	history.AddAndExecuteCommand(std::make_unique<CAddParagraphCommand>(paragraph, items, 0));
	REQUIRE_FALSE(items.empty());
}

TEST_CASE("Can undo command", "[CHistory]")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;

	history.AddAndExecuteCommand(std::make_unique<CAddParagraphCommand>(paragraph, items, 0));
	REQUIRE_FALSE(items.empty());
	REQUIRE(history.CanUndo());
	history.Undo();
	REQUIRE(items.empty());
}

TEST_CASE("Can redo command", "[CHistory]")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;

	history.AddAndExecuteCommand(std::make_unique<CAddParagraphCommand>(paragraph, items, 0));
	REQUIRE_FALSE(items.empty());
	REQUIRE(history.CanUndo());
	history.Undo();
	REQUIRE(items.empty());
	REQUIRE(history.CanRedo());
	history.Redo();
	REQUIRE_FALSE(items.empty());
}

TEST_CASE("Limited by the number of commands", "[CHistory]")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	std::string target;
	for (size_t i = 0; i < 15; ++i)
	{
		history.AddAndExecuteCommand(std::make_unique<CAddParagraphCommand>(paragraph, items, i));
	}
	size_t size = 0;
	size_t expectedSize = 10;

	while (history.CanUndo())
	{
		history.Undo();
		++size;
	}
}

TEST_CASE("Can not undo when clear")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;

	REQUIRE_FALSE(history.CanUndo());
}

TEST_CASE("Can not redo when clear")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	REQUIRE_FALSE(history.CanRedo());
}
