#include "stdafx.h"
#include "CCanvas.h"
#include "CPoint.h"

CCanvas::CCanvas()
{
}

//CCanvas::CCanvas(sf::RenderWindow& window)
//	: m_window(window)
//{
//}

void CCanvas::SetColor(const Color& color)
{
	m_color = color;

	std::cout << "Color: " << m_color << std::endl;
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to)
{
	std::cout << "From (" << from.x << ", " << from.y << ")" << std::endl;
	std::cout << "To (" << to.x << ", " << to.y << ")" << std::endl;
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	std::cout << "Left top (" << left << ", " << top << ")" << std::endl;
	std::cout << "width:" << width << std::endl;
	std::cout << "height:" << height << std::endl;
}
