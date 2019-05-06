#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(PointD leftTop, PointD rightBottom)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

RectD CRectangle::GetFrame() const
{
	double width = m_rightBottom.x - m_leftTop.x;
	double height = m_rightBottom.y - m_leftTop.y;
	return RectD{ m_leftTop.x, m_leftTop.y, width, height };
}

void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTop = PointD{ rect.left, rect.top };
	m_rightBottom = { m_leftTop.x + rect.width, m_leftTop.y + rect.height };
}

void CRectangle::Draw(ICanvas& canvas)
{
	SetCanvasStyles(canvas);
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);
	canvas.LineTo(m_rightBottom.x, m_leftTop.y);
	canvas.LineTo(m_rightBottom.x, m_rightBottom.y);
	canvas.LineTo(m_leftTop.x, m_rightBottom.y);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);
}
