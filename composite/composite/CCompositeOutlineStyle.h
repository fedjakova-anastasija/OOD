#pragma once
#include "CShapes.h"
#include "ICompositeStyle.h"
#include "IOutlineStyle.h"
#include "IStyle.h"

class CCompositeOutlineStyle : public IStyle
{
public:
	CCompositeOutlineStyle(std::shared_ptr<const CShapes> shapes, std::unique_ptr<ICompositeStyle> style)
		: m_shapes(move(shapes))
		, m_style(move(style))
	{
	}

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	//boost::optional<float> GetThickness()const override;
	//void SetThickness(float thickness) override;

private:
	std::shared_ptr<const IShapes> m_shapes;
	std::unique_ptr<ICompositeStyle> m_style;
};