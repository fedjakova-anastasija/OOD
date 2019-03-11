#pragma once
#include "CPoint.h"
#include "CShape.h"
#include "ICanvas.h"

class CEllipse : public CShape
{
public:
	CEllipse(const CPoint& center, double horizontalRadius, double verticalRadius, const Color& color);
	~CEllipse() = default;
	void Draw(ICanvas& canvas) const override;
	CPoint GetCenter() const;
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;

private:
	CPoint m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};
