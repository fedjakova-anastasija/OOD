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
	auto callback = [&](IStyle& style) {
		if (!isEnabled.is_initialized())
		{
			isEnabled = style.IsEnabled();
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = boost::none;
		}
	};

	m_enumerator(callback);
	return isEnabled;
}

optional<RGBAColor> CCompositeFillStyle::GetColor() const
{
	optional<RGBAColor> color;
	auto callback = [&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_enumerator(callback);
	return color;
}