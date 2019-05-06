#pragma once
#include "CShapes.h"
#include "ICompositeStyle.h"
#include "IStyle.h"

class CCompositeFillStyle : public IStyle
{
public:
	CCompositeFillStyle(std::shared_ptr<const CShapes> shapes, std::unique_ptr<ICompositeStyle> style)
		: m_shapes(move(shapes))
		, m_style(move(style))
	{
	}

	optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	std::shared_ptr<const IShapes> m_shapes;
	std::unique_ptr<ICompositeStyle> m_style;
};