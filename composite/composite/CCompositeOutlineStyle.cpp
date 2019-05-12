#include "stdafx.h"
#include "CCompositeOutlineStyle.h"
//#include "CStyle.h"

using namespace std;

CCompositeOutlineStyle::CCompositeOutlineStyle(OutlineStyleEnumerator & enumerator)
	: m_enumerator(enumerator)
{
}

void CCompositeOutlineStyle::Enable(bool enable)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.Enable(enable);
	});
}

void CCompositeOutlineStyle::SetColor(RGBAColor color)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.SetColor(color);
	});
}

optional<bool> CCompositeOutlineStyle::IsEnabled() const
{
	optional<bool> isEnabled;
	auto callback = [&](IOutlineStyle& style) {
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

optional<RGBAColor> CCompositeOutlineStyle::GetColor() const
{
	optional<RGBAColor> color;
	auto callback = [&](IOutlineStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_enumerator(callback);

	return color;
}

optional<float> CCompositeOutlineStyle::GetThickness()const
{
	optional<float> thickness;

	auto callback = [&](IOutlineStyle& style) {
		if (!thickness.is_initialized())
		{
			thickness = style.IsEnabled();
		}
		else if (thickness != style.GetThickness())
		{
			thickness = boost::none;
		}
	};

	m_enumerator(callback);

	return thickness;
}

void CCompositeOutlineStyle::SetThickness(float thickness)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.SetThickness(thickness);
	});
}