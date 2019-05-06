#include "stdafx.h"
#include "CShapeUnit.h"
#include "CStyle.h"

using namespace std;

CShapeUnit::CShapeUnit()
{
	m_fillStyle = make_shared<CStyle>(false, NULL);
	m_outlineStyle = make_shared<CStyle>(true, 0);
}

std::shared_ptr<IStyle> CShapeUnit::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CShapeUnit::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<ICompositeShape> CShapeUnit::GetComposite()
{
	return nullptr;
}

std::shared_ptr<const ICompositeShape> CShapeUnit::GetComposite() const
{
	return nullptr;
}

void CShapeUnit::SetCanvasStyles(ICanvas& canvas)
{
	if (m_outlineStyle->GetColor())
	{
		canvas.SetLineColor(*m_outlineStyle->GetColor());
	}

	if (m_fillStyle->IsEnabled())
	{
		canvas.BeginFill(*m_fillStyle->GetColor());
	}
}