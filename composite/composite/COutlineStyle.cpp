#include "stdafx.h"
#include "COutlineStyle.h"

std::shared_ptr<IStyle> COutlineStyle::GetStyle(std::shared_ptr<IShape> shape)
{
	return shape->GetOutlineStyle();
}
//COutlineStyle::COutlineStyle(bool enabled, RGBAColor color, float thickness)
//	: m_enable(enabled)
//	, m_color(color)
//	, m_thickness(thickness)
//{
//}
//
//boost::optional<bool> COutlineStyle::IsEnabled() const
//{
//	return m_enable;
//}
//
//void COutlineStyle::Enable(bool enable)
//{
//	m_enable = enable;
//}
//
//boost::optional<RGBAColor> COutlineStyle::GetColor() const
//{
//	return m_color;
//}
//
//void COutlineStyle::SetColor(RGBAColor color)
//{
//	m_color = color;
//}
//
//boost::optional<float> COutlineStyle::GetLineThiсkness() const
//{
//	return m_thickness;
//}
//
//void COutlineStyle::SetLineThiсkness(float thikness)
//{
//	m_thickness = thikness;
//}