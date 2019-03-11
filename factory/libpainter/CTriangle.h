#pragma once
#include "CShape.h"
#include "CPoint.h"

class CTriangle : public CShape
{
public:
	CTriangle(const CPoint& first, const CPoint& second, const CPoint& third, const Color& color);
	~CTriangle() = default;
	void Draw(ICanvas& canvas) const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};
