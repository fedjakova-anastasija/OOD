#pragma once
#include "IStyle.h"

class IOutlineStyle : public IStyle
{
public:
	virtual optional<float> GetThickness() const = 0;
	virtual void SetThickness(float thiсkness) = 0;
};