#include "stdafx.h"
#include "CSlide.h"

CSlide::CSlide(double width, double height)
	: m_width(width)
	, m_height(height)
{
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.GetShapesCount();
}

void CSlide::InsertShape(const std::shared_ptr<IShape>& shape)
{
	m_shapes.InsertShape(shape);
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index) const
{
	return m_shapes.GetShapeAtIndex(index);
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	m_shapes.RemoveShapeAtIndex(index);
}

void CSlide::Draw(ICanvas& canvas)
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		auto shape = m_shapes.GetShapeAtIndex(i);
		shape->Draw(canvas);
	}
}