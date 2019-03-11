#pragma once
#include "CPoint.h"
#include "CShape.h"
#include "ICanvas.h"

class CRectangle : public CShape
{
public:
	CRectangle(const CPoint& leftTop, const CPoint& rightBottom, const Color& color);
	~CRectangle() = default;
	void Draw(ICanvas& canvas) const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};
