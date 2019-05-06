#include "stdafx.h"
#include "CFillStyle.h"

std::shared_ptr<IStyle> CFillStyle::GetStyle(std::shared_ptr<IShape> shape)
{
	return shape->GetFillStyle();
}

//using namespace std;
//
//CFillStyle::CFillStyle(bool isEnabled, RGBAColor color)
//	: m_isEnabled(isEnabled)
//	, m_color(color)
//{
//}
//
//optional<bool> CFillStyle::IsEnabled()const
//{
//	return m_isEnabled;
//}
//
//void CFillStyle::Enable(bool enable)
//{
//	m_isEnabled = enable;
//}
//
//optional<RGBAColor> CFillStyle::GetColor()const
//{
//	return m_color;
//}
//
//void CFillStyle::SetColor(RGBAColor color)
//{
//	m_color = color;
//}
