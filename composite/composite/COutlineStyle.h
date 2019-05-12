#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle(bool enabled, RGBAColor color, float thickness);

	optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	optional<float> GetThickness() const override;
	void SetThickness(float thiсkness) override;

private:
	bool m_enabled;
	RGBAColor m_color;
	float m_thickness;
};