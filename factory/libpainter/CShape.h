#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(const Color& color);
	virtual ~CShape() = default;
	virtual void Draw(ICanvas& canvas) const = 0;
	Color GetColor() const;

protected:
	Color m_color;
};
