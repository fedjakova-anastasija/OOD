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
	if (m_shapes->GetShapesCount() == 1)
	{
		return style->IsEnabled();
	}
	else
	{
		if (m_shapes->GetShapesCount() > 1)
		{
			isEnabled = style->IsEnabled();
			for (size_t i = 1; i < m_shapes->GetShapesCount(); i++)
			{
				auto shape = m_shapes->GetShapeAtIndex(i);
				auto style = m_style->GetStyle(shape);

				if (style->IsEnabled() != isEnabled)
				{
					isEnabled = boost::none;
					break;
				}
			}
		}
	}

	return isEnabled;
}

optional<RGBAColor> CCompositeFillStyle::GetColor() const
{
	optional<RGBAColor> color;
	auto shape = m_shapes->GetShapeAtIndex(0);
	auto style = m_style->GetStyle(shape);

	if (m_shapes->GetShapesCount() == 1)
	{
		if (style->IsEnabled())
		{
			return style->GetColor();
		}
	}
	else
	{
		if (m_shapes->GetShapesCount() > 1)
		{
			if (style->IsEnabled())
			{
				color = style->GetColor();
				for (size_t i = 1; i < m_shapes->GetShapesCount(); i++)
				{
					auto shape = m_shapes->GetShapeAtIndex(i);
					auto style = m_style->GetStyle(shape);

					if (style->GetColor() != color || !style->IsEnabled())
					{
						color = boost::none;
						break;
					}
				}
			}
		}
	}

	return color;
}