#include "pch.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Image.h"
#include "ConstPath.h"

TEST_CASE("Can get path")
{
	CHistory history;
	CImage img(IMAGE_PATH, 100, 200, history);
	REQUIRE(img.GetPath().string() == IMAGE_PATH);
}

TEST_CASE("Can get width")
{
	CHistory history;
	CImage img(IMAGE_PATH, 100, 200, history);
	REQUIRE(img.GetWidth() == 100);
}

TEST_CASE("Can get heigh")
{
	CHistory history;
	CImage img(IMAGE_PATH, 100, 200, history);
	REQUIRE(img.GetHeight() == 200);
}

TEST_CASE("Can be resized")
{
	CHistory history;
	CImage img(IMAGE_PATH, 100, 200, history);
	img.Resize(200, 100);
	REQUIRE(img.GetWidth() == 200);
	REQUIRE(img.GetHeight() == 100);
}

TEST_CASE("Can not create wrong path for image")
{
	CHistory history;
	CImage img(IMAGE_PATH, 100, 200, history);
	REQUIRE_THROWS(CImage("/" + IMAGE_PATH, 100, 200, history));
}

TEST_CASE("Can not create wrong extension for image")
{
	CHistory history;
	CImage img(IMAGE_PATH, 100, 200, history);
	std::string path = boost::filesystem::change_extension(IMAGE_PATH, ".doc").string();
	REQUIRE_THROWS(CImage(path, 100, 200, history));
}
