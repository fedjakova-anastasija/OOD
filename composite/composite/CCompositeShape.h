#pragma once
#include "CCompositeFillStyle.h"
#include "CCompositeOutlineStyle.h"
#include "CShapes.h"
#include "ICompositeShape.h"
#include "IOutlineStyle.h"

class CCompositeShape : public ICompositeShape
	, std::enable_shared_from_this<CCompositeShape>
{
public:
	CCompositeShape();

	void Draw(ICanvas& canvas) override;

	ICompositeShape* GetComposite() override;
	std::shared_ptr<const ICompositeShape> GetComposite() const override;

	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle() const override;

	IStyle& GetFillStyle() override;
	const IStyle& GetFillStyle() const override;

	size_t GetShapesCount() const override;
	void InsertShape(const std::shared_ptr<IShape>& shape) override;
	void RemoveShapeAtIndex(size_t index) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

private:
	std::unique_ptr<IStyle> m_fillStyle;
	std::unique_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<CShapes> m_shapes;
};