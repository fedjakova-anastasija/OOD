#pragma once
#include "CShapes.h"
#include "ISlide.h"

class CSlide : public ISlide
{
public:
	//CSlide(double width, double height);
	virtual double GetWidth() const override;
	virtual double GetHeight() const override;

	virtual size_t GetShapesCount() const override;
	virtual void InsertShape(const std::shared_ptr<IShape>& shape) override;
	virtual void RemoveShapeAtIndex(size_t index) override;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;

	virtual void Draw(ICanvas& canvas) override;

private:
	double m_width;
	double m_height;
	CShapes m_shapes;
};