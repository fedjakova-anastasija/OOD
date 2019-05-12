#include "stdafx.h"
#include "CFillStyle.h"

using namespace std;

CFillStyle::CFillStyle(bool isEnabled, RGBAColor color)
	: m_isEnabled(isEnabled)
	, m_color(color)
{
}

optional<bool> CFillStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CFillStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

optional<RGBAColor> CFillStyle::GetColor() const
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}
