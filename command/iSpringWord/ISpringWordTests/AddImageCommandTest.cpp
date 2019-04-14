#include "pch.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Image.h"
#include "../ISpringWord/AddImageCommand.h"
#include "ConstPath.h"

TEST_CASE("Can insert image [AddImageCommand]")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto insertImage = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 100, 100, "images", 0);
	REQUIRE(items.empty());
	insertImage->Execute();
	REQUIRE_FALSE(items.empty());
}

TEST_CASE("Command insert image can be execute")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto insertImage = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 100, 100, "images", 0);
	REQUIRE(items.empty());
	insertImage->Execute();
	REQUIRE_FALSE(items.empty());
	insertImage->Unexecute();
	REQUIRE(items.empty());
}

TEST_CASE("Can create path image")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto insertImage = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 100, 100, "images", 0);
	REQUIRE(items.empty());
	insertImage->Execute();

	auto img = items.front().GetImage();
	REQUIRE(boost::filesystem::exists(img->GetPath()));
}

TEST_CASE("Can delete image")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	auto insertImage = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 100, 100, "images", 0);
	REQUIRE(items.empty());
	insertImage->Execute();

	auto img = items.front().GetImage();
	REQUIRE(boost::filesystem::exists(img->GetPath()));
	insertImage->Unexecute();
	insertImage.reset();
	REQUIRE_FALSE(boost::filesystem::exists(img->GetPath()));
}

TEST_CASE("Can not insert wrong extension file")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	std::string path = boost::filesystem::change_extension(PATH + "image.png", ".doc").string();
	REQUIRE_THROWS(std::make_unique<CAddImageCommand>(history, items, path, 100, 100, "images", 0));
}

TEST_CASE("Can not insert wrong position file")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	
	auto insertImage = std::make_unique<CAddImageCommand>(history, items, PATH + "image.png", 100, 100, "images", 2);
	REQUIRE_THROWS(insertImage->Execute());
}

TEST_CASE("Can not insert wrong path file")
{
	CHistory history;
	std::vector<CDocumentItem> items;
	REQUIRE_THROWS(std::make_unique<CAddImageCommand>(history, items, PATH + "image/" + "image.png", 100, 100, "images", 0));
}