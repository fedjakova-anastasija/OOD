#pragma once
#include "CShapeUnit.h"

class CRectangle : public CShapeUnit
{
public:
	CRectangle(PointD leftTop, PointD rightBottom);

	void SetFrame(const RectD& rect) override;
	RectD GetFrame() const override;

	void Draw(ICanvas& canvas) override;

private:
	PointD m_leftTop;
	PointD m_rightBottom;
};