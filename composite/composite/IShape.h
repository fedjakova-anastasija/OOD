#pragma once
#include "IDrawable.h"
#include "IOutlineStyle.h"
#include "IStyle.h"

class ICompositeShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual const IOutlineStyle& GetOutlineStyle() const = 0;

	virtual IStyle& GetFillStyle() = 0;
	virtual const IStyle& GetFillStyle() const = 0;

	virtual std::shared_ptr<ICompositeShape> GetComposite() = 0;
	virtual std::shared_ptr<const ICompositeShape> GetComposite() const = 0;

	virtual ~IShape() = default;
};