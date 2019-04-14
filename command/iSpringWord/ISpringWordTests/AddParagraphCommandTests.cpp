#include "pch.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/AddParagraphCommand.h"
#include "../ISpringWord/Paragraph.h"

TEST_CASE("Check execute with set position")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	auto insertParagraph = std::make_unique<CAddParagraphCommand>(paragraph, items, 0);
	REQUIRE(items.empty());
	insertParagraph->Execute();

	REQUIRE_FALSE(items.empty());
}

TEST_CASE("Check execute with end position")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	auto insertParagraph = std::make_unique<CAddParagraphCommand>(paragraph, items, boost::none);
	REQUIRE(items.empty());
	insertParagraph->Execute();

	REQUIRE_FALSE(items.empty());
}

TEST_CASE("Check unexecute")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	auto insertParagraph = std::make_unique<CAddParagraphCommand>(paragraph, items, boost::none);
	REQUIRE(items.empty());
	insertParagraph->Execute();
	REQUIRE_FALSE(items.empty());
	insertParagraph->Unexecute();
	REQUIRE(items.empty());
}

TEST_CASE("Can not execute with wrong position")
{
	CHistory history;
	std::string text = "test";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;
	auto insertParagraph = std::make_unique<CAddParagraphCommand>(paragraph, items, 3);
	REQUIRE_THROWS(insertParagraph->Execute());
}