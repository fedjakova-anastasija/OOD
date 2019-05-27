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
	bool differentStates = false;

	m_enumerator([&](IOutlineStyle& style) {
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

optional<RGBAColor> CCompositeOutlineStyle::GetColor() const
{
	optional<RGBAColor> color;
	bool differentColors = false;

	m_enumerator([&](IOutlineStyle& style) {
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

optional<float> CCompositeOutlineStyle::GetThickness() const
{
	optional<float> thickness;
	bool differentThicknesses = false;

	m_enumerator([&](IOutlineStyle& style) {
		if (!thickness.is_initialized())
		{
			thickness = style.GetThickness();
		}
		else if (thickness != style.GetThickness())
		{
			differentThicknesses = true;
		}
	});

	return differentThicknesses ? boost::none : thickness;
}

void CCompositeOutlineStyle::SetThickness(float thickness)
{
	m_enumerator([&thickness](IOutlineStyle& style) {
		style.SetThickness(thickness);
	});
}