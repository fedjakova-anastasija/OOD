#pragma once
#include "IDrawable.h"
#include "IStyle.h"

class ICompositeShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<IStyle> GetOutlineStyle() const = 0;
	virtual std::shared_ptr<IStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<ICompositeShape> GetComposite() = 0;
	virtual std::shared_ptr<const ICompositeShape> GetComposite() const = 0;

	virtual ~IShape() = default;
};