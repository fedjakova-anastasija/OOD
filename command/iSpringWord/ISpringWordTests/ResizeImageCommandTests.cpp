#include "pch.h"
#include "../ISpringWord/ResizeImageCommand.h"

TEST_CASE("Command resize can be executed")
{
	int width = 10;
	int height = 20;
	int newWidth = 30;
	int newHeight = 40;
	auto resizeCommand = std::make_unique<CResizeImageCommand>(width, newWidth, height, newHeight);
	resizeCommand->Execute();

	REQUIRE(newWidth == width);
	REQUIRE(newHeight == height);
}

TEST_CASE("Command resize can be unexecuted")
{
	int width = 10;
	int height = 20;
	int newWidth = 30;
	int newHeight = 40;
	auto resizeCommand = std::make_unique<CResizeImageCommand>(width, newWidth, height, newHeight);
	resizeCommand->Execute();
	resizeCommand->Unexecute();

	REQUIRE_FALSE(newWidth == width);
	REQUIRE_FALSE(newHeight == height);
}
