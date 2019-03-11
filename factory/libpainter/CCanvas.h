#pragma once
#include "Color.h"
#include "ICanvas.h"
#include "CPoint.h"

class CCanvas : public ICanvas
{
public:
	CCanvas();
	~CCanvas() = default;
	void SetColor(const Color& color) override;
	void DrawLine(const CPoint& from, const CPoint& to) override;
	void DrawEllipse(double left, double top, double width, double height) override;

private:
	Color m_color;
};
