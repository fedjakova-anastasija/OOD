#pragma once
#include "IShape.h"
#include "IShapes.h"

class ICompositeShape : public IShape
	, public IShapes
{
public:
	virtual ~ICompositeShape() = default;
};