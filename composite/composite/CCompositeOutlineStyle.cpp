#include "stdafx.h"
#include "CCompositeOutlineStyle.h"

using namespace std;

CCompositeOutlineStyle::CCompositeOutlineStyle(OutlineStyleEnumerator&& enumerator)
	: m_enumerator(enumerator)
{
}

void CCompositeOutlineStyle::Enable(bool enable)
{
	m_enumerator([&enable](IOutlineStyle& style) {
		style.Enable(enable);
	});
}

void CCompositeOutlineStyle::SetColor(RGBAColor color)
{
	m_enumerator([&color](IOutlineStyle& style) {
		style.SetColor(color);
	});
}

optional<bool> CCompositeOutlineStyle::IsEnabled() const
{
	optional<bool> isEnabled;
	m_enumerator([&](IOutlineStyle& style) {
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

optional<RGBAColor> CCompositeOutlineStyle::GetColor() const
{
	optional<RGBAColor> color;
	m_enumerator([&](IOutlineStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	});

	return color;
}

optional<float> CCompositeOutlineStyle::GetThickness() const
{
	optional<float> thickness;

	m_enumerator([&](IOutlineStyle& style) {
		if (!thickness.is_initialized())
		{
			thickness = style.IsEnabled();
		}
		else if (thickness != style.GetThickness())
		{
			thickness = boost::none;
		}
	});

	return thickness;
}

void CCompositeOutlineStyle::SetThickness(float thickness)
{
	m_enumerator([&thickness](IOutlineStyle& style) {
		style.SetThickness(thickness);
	});
}