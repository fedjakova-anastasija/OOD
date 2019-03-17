#pragma once
#include <iostream>
#include <map>
#include <sstream>

enum class Color
{
	GREEN,
	RED,
	BLUE,
	YELLOW,
	PINK,
	BLACK
};

namespace
{
const std::map<std::string, Color> COLOR_STR = {
	{ "green", Color::GREEN },
	{ "red", Color::RED },
	{ "blue", Color::BLUE },
	{ "yellow", Color::YELLOW },
	{ "pink", Color::PINK },
	{ "black", Color::BLACK }
};

const std::map<Color, std::string> COLOR = {
	{ Color::GREEN, "green" },
	{ Color::RED, "red" },
	{ Color::BLUE, "blue" },
	{ Color::YELLOW, "yellow" },
	{ Color::PINK, "pink" },
	{ Color::BLACK, "black" }
};
} // namespace

inline std::istream& operator>>(std::istream& colorStr, Color& color)
{
	std::string str;
	if (colorStr >> str)
	{
		auto it = COLOR_STR.find(str);
		if (it == COLOR_STR.end())
		{
			throw std::invalid_argument("Wrong color name!\nEnter <info> to get valid input\n");
		}
		color = it->second;
	}

	return colorStr;
}

inline std::ostream& operator<<(std::ostream& colorStr, Color& color)
{
	std::string str = "";
	auto it = COLOR.find(color);
	if (it != COLOR.end())
	{
		str = it->second;
	}
	colorStr << str;

	return colorStr;
}