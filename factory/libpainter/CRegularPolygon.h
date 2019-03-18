#pragma once
#include "CShape.h"
#include "ICanvas.h"
#include "CPoint.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(const CPoint& center, double radius, unsigned vertexCount, const Color& color);
	~CRegularPolygon() = default;
	void Draw(ICanvas& canvas) const override;
	unsigned GetVertexCount() const;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	unsigned m_vertexCount;
	CPoint m_center;
	double m_radius;
	std::vector<CPoint> m_vertices;
};
