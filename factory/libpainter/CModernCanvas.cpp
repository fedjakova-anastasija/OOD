//#include "stdafx.h"
//#include "CModernCanvas.h"
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
//void CModernCanvas::DrawLine(const CPoint& from, const CPoint& to)
//{
//	sf::VertexArray line = CreateLine(from, to);
//	m_target.draw(line);
//}
//
//void CModernCanvas::DrawEllipse(double left, double top, double width, double height)
//{
//
//	sf::CircleShape ellipse = CreateEllipse(left, top, width, height);
//	m_target.draw(ellipse);
//}
//
//sf::Vertex CModernCanvas::CreateVertex(const CPoint& point) const
//{
//	sf::Vertex result;
//	result.position = sf::Vector2f(point.x, point.y);
//	result.color = m_color;
//	return result;
//}
//
//sf::VertexArray CModernCanvas::CreateLine(const CPoint& from, const CPoint& to) const
//{
//	sf::VertexArray line(sf::Lines, 2);
//	line[0] = CreateVertex(from);
//	line[1] = CreateVertex(to);
//	return line;
//}
//
//sf::CircleShape CModernCanvas::CreateEllipse(double left, double top, double width, double height) const
//{
//
//	double horizontalRadius = width / 2;
//	double verticalRadius = height / 2;
//
//	sf::CircleShape ellipse(horizontalRadius);
//	ellipse.setOutlineColor(m_color);
//	ellipse.setOutlineThickness(1);
//	ellipse.setScale(1, verticalRadius / horizontalRadius);
//
//	ellipse.setPosition(left, top);
//	return ellipse;
//}