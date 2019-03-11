#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& first, const CPoint& second, const CPoint& third, const Color& color)
	: CShape(color)
	, m_vertex1(first)
	, m_vertex2(second)
	, m_vertex3(third)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
