//#include "stdafx.h"
//#include "CModernCanvas.h"
//#include "Config.h"
//
//CModernCanvas::CModernCanvas(sf::RenderTarget& target)
//	: m_target(target)
//	, m_color(sf::Color::Black)
//{
//}
//
//void CModernCanvas::SetColor(const Color& color)
//{
//	auto result = COLORS.find(color);
//	m_color = result->second;
//}
//
//void CModernCanvas::DrawLine(const CPoint& start, const CPoint& end)
//{
//	sf::Vertex points[] = {
//		sf::Vertex(sf::Vector2f(static_cast<float>(start.x), static_cast<float>(start.y)), m_color),
//
//		sf::Vertex(sf::Vector2f(static_cast<float>(end.x), static_cast<float>(end.y)), m_color)
//	};
//
//	m_target.draw(points, static_cast<size_t>(THICKNESS), sf::Lines);
//}
//
//void CModernCanvas::DrawEllipse(double left, double top, double width, double height)
//{
//	auto horizontalRadius = static_cast<float>(width / 2.f);
//	auto verticalRadius = static_cast<float>(height / 2.f);
//
//	sf::CircleShape ellipse(horizontalRadius);
//	ellipse.setPosition(static_cast<float>(left), static_cast<float>(top));
//	ellipse.setOutlineColor(m_color);
//	ellipse.setOutlineThickness(THICKNESS);
//	ellipse.setScale(1.f, verticalRadius / horizontalRadius);
//
//	m_target.draw(ellipse);
//}