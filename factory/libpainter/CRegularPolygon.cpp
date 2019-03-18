#include "stdafx.h"
#include "CRegularPolygon.h"

CRegularPolygon::CRegularPolygon(const CPoint& center, double radius, unsigned vertexCount, const Color& color)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		double angle = i * 2 * (double)M_PI / m_vertexCount;
		double x = m_center.x + m_radius * std::sin(angle);
		double y = m_center.y + m_radius * std::cos(angle);

		m_vertices.emplace_back(CPoint(x, y));
	}
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);	
	for (auto i = m_vertices.size() - 1; i != 0; --i)
	{
		canvas.DrawLine(m_vertices[i], m_vertices[i - 1]);
	}
	canvas.DrawLine(m_vertices[m_vertices.size() - 1], m_vertices[0]);
}

unsigned CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}
