#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle(bool isEnabled, RGBAColor color);

	virtual optional<bool> IsEnabled() const override;
	virtual void Enable(bool enable) override;

	virtual optional<RGBAColor> GetColor() const override;
	virtual void SetColor(RGBAColor color) override;

private:
	bool m_isEnabled;
	RGBAColor m_color;
};