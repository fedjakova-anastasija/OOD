#include "stdafx.h"
#include "CSlide.h"
#include <algorithm>

//CSlide::CSlide(double width, double height)
//	: m_width(width)
//	, m_height(height)
//{
//}

double CSlide::GetWidth() const
{
	/*if (m_shapes.GetShapesCount() == 0)
	{
		return 0.0;
	}

	RectD firstFrame = m_shapes.GetShapeAtIndex(0)->GetFrame();
	double minX = firstFrame.left;
	double maxX = firstFrame.left + firstFrame.width;

	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		auto shape = m_shapes.GetShapeAtIndex(i);
		RectD frame = shape->GetFrame();
		minX = std::min(minX, frame.left);
		maxX = std::max(maxX, frame.left + frame.width);
	}

	return maxX - minX;*/
	return m_width;
}

double CSlide::GetHeight() const
{
	/*if (m_shapes.GetShapesCount() == 0)
	{
		return 0.0;
	}

	RectD firstFrame = m_shapes.GetShapeAtIndex(0)->GetFrame();
	double minY = firstFrame.top;
	double maxY = firstFrame.top + firstFrame.height;

	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		auto shape = m_shapes.GetShapeAtIndex(i);
		RectD frame = shape->GetFrame();
		minY = std::min(minY, frame.top);
		maxY = std::max(maxY, frame.top + frame.height);
	}

	return maxY - minY;*/
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