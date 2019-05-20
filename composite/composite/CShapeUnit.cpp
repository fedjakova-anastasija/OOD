#include "stdafx.h"
#include "CShapeUnit.h"
#include "CFillStyle.h"
#include "COutlineStyle.h"

using namespace std;

CShapeUnit::CShapeUnit()
{
	m_fillStyle = make_shared<CFillStyle>(false, NULL);
	m_outlineStyle = make_shared<COutlineStyle>(true, 0, 0);
}

IOutlineStyle& CShapeUnit::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IOutlineStyle& CShapeUnit::GetOutlineStyle() const
{
	return *m_outlineStyle;
}

IStyle& CShapeUnit::GetFillStyle()
{
	return *m_fillStyle;
}

const IStyle& CShapeUnit::GetFillStyle() const
{
	return *m_fillStyle;
}

ICompositeShape* CShapeUnit::GetComposite()
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

	if (m_outlineStyle->IsEnabled())
	{
		canvas.SetThickness(m_outlineStyle->GetThickness().get());
	}

	if (m_fillStyle->IsEnabled())
	{
		canvas.BeginFill(*m_fillStyle->GetColor());
	}
}