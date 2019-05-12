#include "stdafx.h"
#include "COutlineStyle.h"

COutlineStyle::COutlineStyle(bool enable, RGBAColor color, float thickness)
	: m_enabled(enable)
	, m_color(color)
	, m_thickness(thickness)
{
}

boost::optional<bool> COutlineStyle::IsEnabled() const
{
	return m_enabled;
}

void COutlineStyle::Enable(bool enable)
{
	m_enabled = enable;
}

boost::optional<RGBAColor> COutlineStyle::GetColor() const
{
	return m_color;
}

void COutlineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

boost::optional<float> COutlineStyle::GetThickness() const
{
	return m_thickness;
}

void COutlineStyle::SetThickness(float thickness)
{
	m_thickness = thickness;
}