#include "lwtasktest.h"
#include "pch.h"


TEST_CASE("There is an opportunity to move to the point")
{
	std::stringstream strm;
	modern_graphics_lib::CModernGraphicsRenderer renderer(strm);
	app::CAdapter adapter(renderer);

	adapter.MoveTo(10, 15);
	REQUIRE(strm.str() == "<draw>\n");
}

TEST_CASE("There is an opportunity to draw the line")
{
	std::stringstream strm;
	modern_graphics_lib::CModernGraphicsRenderer renderer(strm);
	app::CAdapter adapter(renderer);

	adapter.MoveTo(30, 40);
	adapter.LineTo(30, 64);

	REQUIRE(strm.str() == "<draw>\n""  <line fromX=\"30\" fromY=\"40\" toX=\"30\" toY=\"64\"/>\n");
}