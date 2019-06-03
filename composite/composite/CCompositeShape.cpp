#include "stdafx.h"
#include "CCompositeShape.h"
#include "CShapes.h"

using namespace std;

CCompositeShape::CCompositeShape()
{
	m_shapes = make_shared<CShapes>();

	m_fillStyle = make_unique<CCompositeFillStyle>([this](function<void(IStyle&)> callback) {
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			callback(shape->GetFillStyle());
		}
	});

	m_outlineStyle = make_unique<CCompositeOutlineStyle>([this](function<void(IOutlineStyle&)> callback) {
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			callback(shape->GetOutlineStyle());
		}
	});
}

void CCompositeShape::Draw(ICanvas& canvas)
{
	for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
	{
		auto shape = m_shapes->GetShapeAtIndex(i);
		shape->Draw(canvas);
	}
}

IOutlineStyle& CCompositeShape::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IOutlineStyle& CCompositeShape::GetOutlineStyle() const
{
	return *m_outlineStyle;
}

IStyle& CCompositeShape::GetFillStyle()
{
	return *m_fillStyle;
}

const IStyle& CCompositeShape::GetFillStyle() const
{
	return *m_fillStyle;
}

std::shared_ptr<ICompositeShape> CCompositeShape::GetComposite()
{
	return shared_from_this();
}

std::shared_ptr<const ICompositeShape> CCompositeShape::GetComposite() const
{
	return shared_from_this();
}

RectD CCompositeShape::GetFrame() const
{
	std::exception_ptr p;
	try
	{
		if (m_shapes->GetShapesCount() == 0)
		{
			throw std::logic_error("Empty group frame!");
		}

		RectD firstFrame = m_shapes->GetShapeAtIndex(0)->GetFrame();

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

		firstFrame = { minX, minY, maxX - minX, maxY - minY };
		return firstFrame;
	}
	catch (const std::exception& e)
	{
		return {0.f, 0.f, 0.f, 0.f};
		p = std::current_exception();
		std::cout << e.what() << std::endl;
	}
}

void CCompositeShape::SetFrame(const RectD& frame)
{
	std::exception_ptr p;
	try
	{
		if (m_shapes->GetShapesCount() == 0)
		{
			throw std::logic_error("Empty group frame!");
		}

		RectD oldFrame = GetFrame();

		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			RectD shapeFrame = shape->GetFrame();
			shapeFrame.left = frame.left + (shapeFrame.left - oldFrame.left) / (oldFrame.width / frame.width);
			shapeFrame.top = frame.top + (shapeFrame.top - oldFrame.top) / (oldFrame.height / frame.height);
			shapeFrame.width = shapeFrame.width * (frame.width / oldFrame.width);
			shapeFrame.height = shapeFrame.height * (frame.height / oldFrame.height);

			shape->SetFrame(shapeFrame);
		}
	}
	catch (const std::exception& e)
	{
		p = std::current_exception();
		std::cout << e.what() << std::endl;
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