#include "stdafx.h"
#include "CEllipse.h"

CEllipse::CEllipse(const CPoint& center, double horizontalRadius, double verticalRadius, const Color& color)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	double left = m_center.x - m_horizontalRadius / 2;
	double top = m_center.y - m_verticalRadius / 2;
	double width = m_horizontalRadius * 2;
	double height = m_verticalRadius * 2;
	canvas.DrawEllipse(left, top, width, height);
}

CPoint CEllipse::GetCenter() const
{
	return m_center;
}

double CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

double CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}
