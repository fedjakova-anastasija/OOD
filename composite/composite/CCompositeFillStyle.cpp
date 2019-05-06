#include "stdafx.h"
#include "CCompositeFillStyle.h"
#include "CStyle.h"

using namespace std;

void CCompositeFillStyle::Enable(bool enable)
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

void CCompositeFillStyle::SetColor(RGBAColor color)
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

optional<bool> CCompositeFillStyle::IsEnabled() const
{
	optional<bool> isEnabled;
	auto shape = m_shapes->GetShapeAtIndex(0);
	auto style = m_style->GetStyle(shape);
	return style->IsEnabled();
}

optional<RGBAColor> CCompositeFillStyle::GetColor() const
{
	optional<RGBAColor> color;
	auto shape = m_shapes->GetShapeAtIndex(0);
	auto style = m_style->GetStyle(shape);
	return style->GetColor();
}