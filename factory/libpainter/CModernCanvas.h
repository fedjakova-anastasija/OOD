//#pragma once
//#include "CPoint.h"
//#include "Color.h"
//#include "ICanvas.h"
#pragma once
#include "CPoint.h"
#include "Color.h"
#include "ICanvas.h"

class CModernCanvas : public ICanvas
{
public:
	CModernCanvas(sf::RenderWindow& window);
	~CModernCanvas() = default;
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
	sf::Vertex CreateVertex(const CPoint& point) const;
	sf::VertexArray CreateLine(const CPoint& from, const CPoint& to) const;
	//sf::CircleShape CreateEllipse(double left, double top, double width, double height) const;
};

//class CModernCanvas : public ICanvas
//{
//public:
//	CModernCanvas(sf::RenderTarget&);
//	void SetColor(const Color& color) override;
//	void DrawLine(const CPoint& from, const CPoint& to) override;
//	void DrawEllipse(double left, double top, double width, double height) override;
//
//private:
//	sf::RenderTarget& m_target;
//	sf::Color m_color;
//	const std::map<Color, sf::Color> COLORS = { { Color::BLACK, sf::Color::Black },
//		{ Color::BLUE, sf::Color::Blue },
//		{ Color::GREEN, sf::Color::Green },
//		{ Color::PINK, sf::Color(255, 105, 180) },
//		{ Color::RED, sf::Color::Red }  ,
//		{ Color::YELLOW, sf::Color::Yellow } };
//	sf::Vertex CreateVertex(const CPoint& point) const;
//	sf::VertexArray CreateLine(const CPoint& from, const CPoint& to) const;
//	sf::CircleShape CreateEllipse(double left, double top, double width, double height) const;
//};
