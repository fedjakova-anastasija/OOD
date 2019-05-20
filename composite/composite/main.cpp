#include "stdafx.h"
#include "CCanvas.h"
#include "CCompositeShape.h"
#include "CEllipse.h"
#include "CRectangle.h"
#include "CSlide.h"
#include "CTriangle.h"
#include "CommonTypes.h"

using namespace std;

int main()
{
	string fileName = "canvas";
	string fileExtension = "svg";
	string file = fileName + "." + fileExtension;

	ofstream inputFile(file);
	CCanvas canvas(inputFile, 600, 600);
	CSlide slide(500, 500);

	//sun
	auto sun = make_shared<CEllipse>(PointD{ 100, 100 }, 20, 20);
	sun->GetFillStyle().SetColor(0xffeb3b);
	sun->GetOutlineStyle().SetColor(0xffd700);
	sun->GetOutlineStyle().SetThickness(5);

	sun->Draw(canvas);

	//house body
	auto houseBody = make_shared<CRectangle>(PointD{ 200, 300 }, PointD{ 300, 200 });
	houseBody->GetFillStyle().SetColor(0x8B4513);
	houseBody->GetOutlineStyle().SetColor(0x000000);
	houseBody->GetOutlineStyle().SetThickness(2);

	houseBody->Draw(canvas);

	//house roof

	auto houseRoof = make_shared<CTriangle>(PointD{ 180, 200 }, PointD{ 250, 150 }, PointD{ 320, 200 });
	houseRoof->GetFillStyle().SetColor(0x808080);
	houseRoof->GetOutlineStyle().SetColor(0x000000);
	houseRoof->GetOutlineStyle().SetThickness(2);

	houseRoof->Draw(canvas);

	//house body
	auto emptyRectangle = make_shared<CRectangle>(PointD{ 0, 0 }, PointD{ 0, 0 });

	emptyRectangle->Draw(canvas);

	auto house = make_shared<CCompositeShape>();
	auto emptyGroup = make_shared<CCompositeShape>();

	house->InsertShape(houseBody);
	house->InsertShape(houseRoof);
	house->SetFrame({ 500, 150, 50, 50 });
	//emptyGroup->SetFrame({ 0, 0, 0, 0 });
	std::cout << "Frame: " << house->GetFrame().height << " " << house->GetFrame().width << std::endl;
	//std::cout << "Frame: " << emptyGroup->GetFrame().height << " " << emptyGroup->GetFrame().width << std::endl;
	//house->InsertShape(emptyRectangle);
	house->InsertShape(emptyGroup);
	std::cout << "Frame: " << house->GetFrame().height << " " << house->GetFrame().width << std::endl;
	//std::cout << "Frame: " << emptyGroup->GetFrame().height << " " << emptyGroup->GetFrame().width << std::endl;
	
	house->GetOutlineStyle().SetColor(0x0000ff);
	house->GetFillStyle().SetColor(0x0000ff);
	house->GetOutlineStyle().SetThickness(5);
	
	slide.InsertShape(house);
	slide.Draw(canvas);

	return 0;
}

//#include <cstdint>
//#include "CommonTypes.h"
//#include "Canvas.h"
//#include "version1.h"
//
//#include <boost/optional.hpp>
//#include <memory>
//#include <limits>
//#include <functional>
//
//using boost::optional;
//
//class IDrawable
//{
//public:
//	virtual void Draw(const ICanvas & canvas) = 0;
//
//	virtual ~IDrawable() = default;
//};
//
//class IStyle
//{
//public:
//	virtual optional<bool> IsEnabled()const = 0;
//	virtual void Enable(bool enable) = 0;
//
//	virtual optional<RGBAColor> GetColor()const = 0;
//	virtual void SetColor(RGBAColor color) = 0;
//
//	virtual ~IStyle() = default;
//};
//
//class IGroupShape;
//
//class IShape : public IDrawable
//{
//public:
//	virtual RectD GetFrame() = 0;
//	virtual void SetFrame(const RectD & rect) = 0;
//
//	virtual IStyle & GetOutlineStyle() = 0;
//	virtual const IStyle & GetOutlineStyle()const = 0;
//
//	virtual IStyle & GetFillStyle() = 0;
//	virtual const IStyle & GetFillStyle()const = 0;
//
//	virtual std::shared_ptr<IGroupShape> GetComposite() = 0;
//	virtual std::shared_ptr<const IGroupShape> GetComposite() const = 0;
//
//	virtual ~IShape() = default;
//};
//
//class IShapes
//{
//public:
//	virtual size_t GetShapesCount()const = 0;
//	virtual void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
//	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
//	virtual void RemoveShapeAtIndex(size_t index) = 0;
//
//	virtual ~IShapes() = default;
//};
//
//class IGroupShape : public IShape, public IShapes
//{
//public:
//	virtual ~IGroupShape() = default;
//};
//
//typedef std::function<void(ICanvas & canvas, const IShape & shape)> DrawingStrategy;
//
//class CShapeUnit : public IShape
//{
//public:
//	CShapeUnit(const DrawingStrategy & drawingStrategy)
//	{
//		(void)&drawingStrategy;
//	}
//};
//
//class CGroupShape : public IGroupShape
//{
//
//};
//
//class ISlide : public IDrawable
//{
//public:
//	virtual double GetWidth()const = 0;
//	virtual double GetHeight()const = 0;
//
//	virtual IShapes & GetShapes()const = 0;
//
//	virtual ~ISlide() = default;
//};
//
//class CSlide : public ISlide
//{
//public:
//
//};
//
//
//int main()
//{
//
//}
