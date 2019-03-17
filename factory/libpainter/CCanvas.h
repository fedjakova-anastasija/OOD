#pragma once
#include "Color.h"
#include "ICanvas.h"
#include "CPoint.h"

//class CCanvas : public ICanvas
//{
//public:
//	CCanvas();
//	~CCanvas() = default;
//	void SetColor(const Color& color) override;
//	void DrawLine(const CPoint& from, const CPoint& to) override;
//	void DrawEllipse(double left, double top, double width, double height) override;
//
//private:
//	Color m_color;
//};

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	~CCanvas() = default;
	void SetColor(const Color& color) override;
	void DrawLine(const CPoint& from, const CPoint& to) override;
	void DrawEllipse(double left, double top, double width, double height) override;

private:
	sf::RenderWindow& m_window;
	sf::Color m_color;
	const std::map<Color, sf::Color> COLORS = { { Color::BLACK, sf::Color::Black },
		{ Color::BLUE, sf::Color::Blue },
		{ Color::GREEN, sf::Color::Green },
		{ Color::PINK, sf::Color(255, 105, 180) },
		{ Color::RED, sf::Color::Red },
		{ Color::YELLOW, sf::Color::Yellow } };
};

