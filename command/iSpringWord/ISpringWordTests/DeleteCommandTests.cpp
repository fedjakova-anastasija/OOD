#include "pch.h"
#include "../ISpringWord/DeleteCommand.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Image.h"
#include "../ISpringWord/AddImageCommand.h"
#include "ConstPath.h"

TEST_CASE("Command delete can be executed ")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto image = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 1000, 500, "images", 0);
	image->Execute();
	REQUIRE_FALSE(items.empty());
	auto deleteItem = std::make_unique<CDeleteCommand>(items, 0);
	deleteItem->Execute();
	REQUIRE(items.empty());
}

TEST_CASE("Command delete can be unexecuted")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto image = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 1000, 500, "images", 0);
	image->Execute();
	REQUIRE_FALSE(items.empty());
	auto deleteItem = std::make_unique<CDeleteCommand>(items, 0);
	deleteItem->Execute();
	REQUIRE(items.empty());
	deleteItem->Unexecute();
	REQUIRE_FALSE(items.empty());
}

TEST_CASE("Can not delete history image")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto image = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 1000, 500, "images", 0);
	image->Execute();
	auto img = items.front().GetImage();
	REQUIRE(boost::filesystem::exists(img->GetPath()));

	auto deleteItem = std::make_unique<CDeleteCommand>(items, 0);
	deleteItem->Execute();
	REQUIRE(boost::filesystem::exists(img->GetPath()));
}

TEST_CASE("Can not delete history image with unexecuted command")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto image = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 1000, 500, "images", 0);
	image->Execute();
	auto img = items.front().GetImage();
	REQUIRE(boost::filesystem::exists(img->GetPath()));

	auto deleteItem = std::make_unique<CDeleteCommand>(items, 0);
	deleteItem->Execute();
	deleteItem->Unexecute();
	REQUIRE(boost::filesystem::exists(img->GetPath()));
}
