#include "stdafx.h"
#include "CCompositeFillStyle.h"

using namespace std;

CCompositeFillStyle::CCompositeFillStyle(FillStyleEnumerator&& enumerator)
	: m_enumerator(enumerator)
{
}

void CCompositeFillStyle::Enable(bool enable)
{
	m_enumerator([&enable](IStyle& style) {
		style.Enable(enable);
	});
}

void CCompositeFillStyle::SetColor(RGBAColor color)
{
	m_enumerator([&color](IStyle& style) {
		style.SetColor(color);
	});
}

optional<bool> CCompositeFillStyle::IsEnabled() const
{
	optional<bool> isEnabled;
	bool differentStates = false;

	m_enumerator([&](IStyle& style) {
		if (!isEnabled.is_initialized())
		{
			isEnabled = style.IsEnabled();
		}
		else if (style.IsEnabled() != isEnabled)
		{
			differentStates = true;
		}
	});

	return differentStates ? boost::none : isEnabled;
}

optional<RGBAColor> CCompositeFillStyle::GetColor() const
{
	optional<RGBAColor> color;
	bool differentColors = false;

	m_enumerator([&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
		else if (style.GetColor() != color)
		{
			differentColors = true;
		}
	});

	return differentColors ? boost::none : color;
}