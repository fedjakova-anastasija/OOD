#pragma once
#include "CPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void SetColor(const Color& color) = 0;
	virtual void DrawLine(const CPoint& from, const CPoint& to) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
};
