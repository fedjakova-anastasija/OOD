#pragma once
#include "ICanvas.h"
#include "IShape.h"

class CShapeUnit : public IShape
{
public:
	CShapeUnit();
	virtual std::shared_ptr<ICompositeShape> GetComposite() override;
	virtual std::shared_ptr<const ICompositeShape> GetComposite() const override;

	virtual std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	virtual std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;

	virtual std::shared_ptr<IStyle> GetFillStyle() override;
	virtual std::shared_ptr<const IStyle> GetFillStyle() const override;

	void SetCanvasStyles(ICanvas& canvas);

protected:
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};