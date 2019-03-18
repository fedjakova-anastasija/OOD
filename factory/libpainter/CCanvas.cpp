#include "stdafx.h"
#include "CCanvas.h"
#include "CPoint.h"
#include "Config.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
	, m_color(sf::Color::Black)
{
}

void CCanvas::SetColor(const Color& color)
{
	auto result = COLORS.find(color);
	m_color = result->second;
}

void CCanvas::DrawLine(const CPoint& start, const CPoint& end)
{
	sf::Vertex points[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(start.x), static_cast<float>(start.y)), m_color),

		sf::Vertex(sf::Vector2f(static_cast<float>(end.x), static_cast<float>(end.y)), m_color)
	};

	m_window.draw(points, static_cast<size_t>(THICKNESS), sf::Lines);
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	auto horizontalRadius = static_cast<float>(width / 2.f);
	auto verticalRadius = static_cast<float>(height / 2.f);

	sf::CircleShape ellipse(horizontalRadius);
	ellipse.setPosition(static_cast<float>(left), static_cast<float>(top));
	ellipse.setOutlineColor(m_color);
	ellipse.setOutlineThickness(THICKNESS);
	ellipse.setScale(1.f, verticalRadius / horizontalRadius);

	m_window.draw(ellipse);
}