#pragma once
#include "ICompositeStyle.h"
#include "IOutlineStyle.h"

class COutlineStyle : public ICompositeStyle
{
public:
	std::shared_ptr<IStyle> GetStyle(std::shared_ptr<IShape> shape) override;
};
