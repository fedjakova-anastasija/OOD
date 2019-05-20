#pragma once
#include "IOutlineStyle.h"

typedef std::function<void(std::function<void(IOutlineStyle&)>)> OutlineStyleEnumerator;

class CCompositeOutlineStyle : public IOutlineStyle
{
public:
	CCompositeOutlineStyle(OutlineStyleEnumerator&& enumerator);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	boost::optional<float> GetThickness() const override;
	void SetThickness(float thickness) override;

private:
	OutlineStyleEnumerator m_enumerator;
};