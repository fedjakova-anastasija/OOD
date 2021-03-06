#include "lwtaskAdapterColorTest.h"
#include "pch.h"

TEST_CASE("There is an opportunity to set color")
{
	std::stringstream strm;
	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(strm);
	app::CRendererAdapter adapter(renderer);
	
	adapter.SetColor(0xFF0000);
	adapter.MoveTo(30, 40);
	adapter.LineTo(30, 64);
	REQUIRE(strm.str() == "<draw>\n""  <line fromX=\"30\" fromY=\"40\" toX=\"30\" toY=\"64\"/>\n""    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n""  </line>\n");
}

TEST_CASE("There is an opportunity to move to the point")
{
	std::stringstream strm;
	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(strm);
	app::CRendererAdapter adapter(renderer);

	adapter.MoveTo(10, 15);
	REQUIRE(strm.str() == "<draw>\n");
}

TEST_CASE("There is an opportunity to draw the line")
{
	std::stringstream strm;
	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(strm);
	app::CRendererAdapter adapter(renderer);

	adapter.MoveTo(30, 40);
	adapter.LineTo(30, 64);

	REQUIRE(strm.str() == "<draw>\n""  <line fromX=\"30\" fromY=\"40\" toX=\"30\" toY=\"64\"/>\n""    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n""  </line>\n");
}