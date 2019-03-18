#pragma once
#include "CPoint.h"
#include "Color.h"
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	~CCanvas() = default;
	void SetColor(const Color& color) override;
	void DrawLine(const CPoint& from, const CPoint& to) override;
	void DrawEllipse(double left, double top, double width, double height) override;

private:
	const std::map<Color, sf::Color> COLORS = {
		{ Color::GREEN, sf::Color::Green },
		{ Color::RED, sf::Color::Red },
		{ Color::BLUE, sf::Color::Blue },
		{ Color::YELLOW, sf::Color::Yellow },
		{ Color::PINK, sf::Color(0xFF, 0xB6, 0xC1) },
		{ Color::BLACK, sf::Color::Black }
	};

	sf::RenderWindow& m_window;
	sf::Color m_color;
};
