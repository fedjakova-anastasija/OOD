#include "stdafx.h"
#include "CEllipse.h"

CEllipse::CEllipse(PointD center, double horRadius, double verRadius)
	: m_center(center)
	, m_horRadius(horRadius)
	, m_verRadius(verRadius)
{
}

RectD CEllipse::GetFrame() const
{
	auto point = PointD{ m_center.x - m_horRadius, m_center.y - m_verRadius };
	return RectD{ point.x, point.y, 2 * m_horRadius, 2 * m_verRadius };
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_center = PointD{ rect.left + rect.width / 2, rect.top + rect.height / 2 };
	m_horRadius = rect.width / 2;
	m_verRadius = rect.height / 2;
}
void CEllipse::Draw(ICanvas& canvas)
{
	SetCanvasStyles(canvas);
	canvas.DrawEllipse(m_center.x, m_center.y, 2 * m_horRadius, 2 * m_verRadius);
}