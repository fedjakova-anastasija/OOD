#pragma once
#include "CShapeUnit.h"

class CTriangle : public CShapeUnit
{
public:
	CTriangle(PointD one, PointD two, PointD three);

	virtual RectD GetFrame() const final;
	virtual void SetFrame(const RectD& rect) final;

	void Draw(ICanvas& canvas) final;

private:
	PointD m_firstPoint = { 0, 0 };
	PointD m_secondPoint = { 0, 0 };
	PointD m_thirdPoint = { 0, 0 };
};