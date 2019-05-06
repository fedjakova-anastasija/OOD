#include "stdafx.h"
#include "CCompositeShape.h"
#include "CCompositeFillStyle.h"
#include "CCompositeOutlineStyle.h"
#include "CFillStyle.h"
#include "COutlineStyle.h"
#include "CStyle.h"

using namespace std;

CCompositeShape::CCompositeShape()
{
	m_shapes = make_shared<CShapes>();
	m_fillStyle = make_shared<CCompositeFillStyle>(m_shapes, make_unique<CFillStyle>());
	m_outlineStyle = make_shared<CCompositeOutlineStyle>(m_shapes, make_unique<COutlineStyle>());
}

void CCompositeShape::Draw(ICanvas& canvas)
{
	for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
	{
		auto shape = m_shapes->GetShapeAtIndex(i);
		shape->Draw(canvas);
	}
}

shared_ptr<IStyle> CCompositeShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

shared_ptr<IStyle> CCompositeShape::GetFillStyle() const
{
	return m_fillStyle;
}

shared_ptr<ICompositeShape> CCompositeShape::GetComposite()
{
	return make_shared<CCompositeShape>(*this);
}

shared_ptr<const ICompositeShape> CCompositeShape::GetComposite() const
{
	return make_shared<CCompositeShape>(*this);
}

RectD CCompositeShape::GetFrame() const
{
	RectD frame = { 0, 0, 0, 0 };

	if (m_shapes->GetShapesCount() != 0)
	{
		RectD const& firstFrame = m_shapes->GetShapeAtIndex(0)->GetFrame();

		double minX = firstFrame.left;
		double minY = firstFrame.top;
		double maxX = minX + firstFrame.width;
		double maxY = minY + firstFrame.height;

		if (m_shapes->GetShapesCount() > 0)
		{
			for (size_t i = 1; i < m_shapes->GetShapesCount(); i++)
			{
				auto shape = m_shapes->GetShapeAtIndex(i);

				RectD const& frame = shape->GetFrame();
				minX = min(minX, frame.left);
				minY = min(minY, frame.top);
				maxX = max(maxX, frame.left + frame.width);
				maxY = max(maxY, frame.top + frame.height);
			}
		}

		frame = { minX, minY, maxX - minX, maxY - minY };
	}

	return frame;
}

void CCompositeShape::SetFrame(const RectD& rect)
{
	RectD oldFrame = GetFrame();

	for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
	{
		auto shape = m_shapes->GetShapeAtIndex(i);

		RectD shapeFrame = shape->GetFrame();
		shapeFrame.left = rect.left + (shapeFrame.left - oldFrame.left) / (oldFrame.width / rect.width);
		shapeFrame.top = rect.top + (shapeFrame.top - oldFrame.top) / (oldFrame.height / rect.height);
		shapeFrame.width = shapeFrame.width * (rect.width / oldFrame.width);
		shapeFrame.height = shapeFrame.height * (rect.height / oldFrame.height);
		shape->SetFrame(shapeFrame);
	}
}

size_t CCompositeShape::GetShapesCount() const
{
	return m_shapes->GetShapesCount();
}

void CCompositeShape::InsertShape(const std::shared_ptr<IShape>& shape)
{
	m_shapes->InsertShape(shape);
}

std::shared_ptr<IShape> CCompositeShape::GetShapeAtIndex(size_t index) const
{
	return m_shapes->GetShapeAtIndex(index);
}

void CCompositeShape::RemoveShapeAtIndex(size_t index)
{
	m_shapes->RemoveShapeAtIndex(index);
}