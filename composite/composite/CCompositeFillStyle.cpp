#include "stdafx.h"
#include "CCompositeFillStyle.h"

using namespace std;

CCompositeFillStyle::CCompositeFillStyle(FillStyleEnumerator& enumerator)
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
	m_enumerator([&](IStyle& style) {
		if (!isEnabled.is_initialized())
		{
			isEnabled = style.IsEnabled();
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = boost::none;
		}
	});

	return isEnabled;
}

optional<RGBAColor> CCompositeFillStyle::GetColor() const
{
	optional<RGBAColor> color;
	m_enumerator([&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	});

	return color;
}