#include "pch.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Paragraph.h"

TEST_CASE("Paragraph can be created")
{
	CHistory history;
	std::string text = "test";
	CParagraph paragraph(history, text);
	REQUIRE(paragraph.GetText() == text);
}

TEST_CASE("Paragraph can be set")
{
	CHistory history;
	std::string text = "test";
	CParagraph paragraph(history, text);
	paragraph.SetText(text);
	REQUIRE(paragraph.GetText() == text);
}
