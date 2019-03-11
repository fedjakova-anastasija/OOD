#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, const CPoint& rightBottom, const Color& color)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	const CPoint rightTop(m_rightBottom.x, m_leftTop.y);
	const CPoint leftBottom(m_leftTop.x, m_rightBottom.y);

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}
