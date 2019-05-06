#include "stdafx.h"
#include "CCompositeOutlineStyle.h"
#include "CStyle.h"

using namespace std;

void CCompositeOutlineStyle::Enable(bool enable)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = m_style->GetStyle(shape);
			style->Enable(true);
		}
	}
}

void CCompositeOutlineStyle::SetColor(RGBAColor color)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = m_style->GetStyle(shape);
			style->SetColor(color);
		}
	}
}

optional<bool> CCompositeOutlineStyle::IsEnabled() const
{
	optional<bool> isEnabled;
	auto shape = m_shapes->GetShapeAtIndex(0);
	auto style = m_style->GetStyle(shape);
	return style->IsEnabled();
}

optional<RGBAColor> CCompositeOutlineStyle::GetColor() const
{
	optional<RGBAColor> color;
	auto shape = m_shapes->GetShapeAtIndex(0);
	auto style = m_style->GetStyle(shape);
	return style->GetColor();
}

//optional<float> CCompositeOutlineStyle::GetThickness()const
//{
//	if (m_shapes->GetShapesCount() != 0)
//	{
//		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
//		{
//			GetThickness();
//		}
//	}
//}
//
//void CCompositeOutlineStyle::SetThickness(float thickness)
//{
//	if (m_shapes->GetShapesCount() != 0)
//	{
//		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
//		{
//			SetThickness(thickness);
//		}
//	}
//}