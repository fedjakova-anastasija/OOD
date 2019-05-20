#pragma once
#include "ICanvas.h"
#include "IShape.h"

class CShapeUnit : public IShape
{
public:
	CShapeUnit();
	virtual std::shared_ptr<ICompositeShape> GetComposite() override;
	virtual std::shared_ptr<const ICompositeShape> GetComposite() const override;

	virtual IOutlineStyle& GetOutlineStyle() override;
	virtual const IOutlineStyle& GetOutlineStyle() const override;

	virtual IStyle& GetFillStyle() override;
	virtual const IStyle& GetFillStyle() const override;

	void SetCanvasStyles(ICanvas& canvas);

protected:
	std::unique_ptr<IOutlineStyle> m_outlineStyle;
	std::unique_ptr<IStyle> m_fillStyle;
};