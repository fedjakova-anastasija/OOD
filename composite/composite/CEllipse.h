#pragma once
#include "CShapeUnit.h"

class CEllipse : public CShapeUnit
{
public:
	CEllipse(PointD center, double horRadius, double verRadius);

	virtual void SetFrame(const RectD& rect) final;
	virtual RectD GetFrame() const final;

	void Draw(ICanvas& canvas) final;

private:
	PointD m_center = { 0, 0 };
	double m_horRadius = 0;
	double m_verRadius = 0;
};