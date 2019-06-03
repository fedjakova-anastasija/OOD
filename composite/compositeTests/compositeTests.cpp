#include "../composite/CCompositeFillStyle.cpp"
#include "../composite/CCompositeOutlineStyle.cpp"
#include "../composite/CCompositeShape.cpp"
#include "../composite/CCompositeShape.h"
#include "../composite/CEllipse.cpp"
#include "../composite/CEllipse.h"
#include "../composite/CFillStyle.cpp"
#include "../composite/COutlineStyle.cpp"
#include "../composite/CRectangle.cpp"
#include "../composite/CRectangle.h"
#include "../composite/CShapeUnit.cpp"
#include "../composite/CShapes.cpp"
#include "../composite/CTriangle.cpp"
#include "../composite/CTriangle.h"
#include "pch.h"

TEST_CASE("A number of shapes is zero when group was created")
{
	auto group = std::make_shared<CCompositeShape>();
	REQUIRE(group->GetShapesCount() == 0);
}

TEST_CASE("New group has empty frame")
{
	auto group = std::make_shared<CCompositeShape>();
	auto groupFrame = group->GetFrame();

	REQUIRE(groupFrame.left == NAN);
	REQUIRE(groupFrame.top == NAN);
	REQUIRE(groupFrame.width == NAN);
	REQUIRE(groupFrame.height == NAN);
}

TEST_CASE("New group can not set frame")
{
	auto group = std::make_shared<CCompositeShape>();
	REQUIRE_NOTHROW(group->SetFrame({ 10, 10, 10, 10 }));
}

TEST_CASE("New empty group can not get style")
{
	auto group = std::make_shared<CCompositeShape>();
	REQUIRE(group->GetOutlineStyle().GetColor() == boost::none);
	REQUIRE(group->GetOutlineStyle().IsEnabled() == boost::none);
	REQUIRE(group->GetFillStyle().GetColor() == boost::none);
	REQUIRE(group->GetFillStyle().IsEnabled() == boost::none);
	REQUIRE(group->GetOutlineStyle().GetThickness() == boost::none);
}

TEST_CASE("The group can add a rectangle")
{
	auto group = std::make_shared<CCompositeShape>();
	auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, PointD{ 50, 100 });
	group->InsertShape(rectangle);
	REQUIRE(group->GetShapesCount() == 1);
}

TEST_CASE("The group can add a triangle")
{
	auto group = std::make_shared<CCompositeShape>();
	auto triangle = std::make_shared<CTriangle>(PointD{ 180, 200 }, PointD{ 250, 150 }, PointD{ 320, 200 });
	group->InsertShape(triangle);
	REQUIRE(group->GetShapesCount() == 1);
}

TEST_CASE("The group can add an ellipse")
{
	auto group = std::make_shared<CCompositeShape>();
	auto ellipse = std::make_shared<CEllipse>(PointD{ 100, 100 }, 20, 20);
	group->InsertShape(ellipse);
	REQUIRE(group->GetShapesCount() == 1);
}

TEST_CASE("The group can remove shape")
{
	auto group = std::make_shared<CCompositeShape>();
	auto ellipse = std::make_shared<CEllipse>(PointD{ 100, 100 }, 20, 20);
	group->InsertShape(ellipse);
	REQUIRE(group->GetShapesCount() == 1);
	REQUIRE_THROWS_WITH(group->RemoveShapeAtIndex(1), "Wrong index!");
	group->RemoveShapeAtIndex(0);
	REQUIRE(group->GetShapesCount() == 0);
}

TEST_CASE("CGroupShape with shapes", "[CGroupShape]")
{
	auto group = std::make_shared<CCompositeShape>();
	auto rectangle = std::make_shared<CRectangle>(PointD{ 10, 10 }, PointD{ 20, 20 });
	auto newRectangle = std::make_shared<CRectangle>(PointD{ 10, 10 }, PointD{ 20, 20 });

	rectangle->GetFillStyle().SetColor(0x000000);
	rectangle->GetOutlineStyle().SetColor(0x000000);
	rectangle->GetOutlineStyle().SetThickness(2);
	group->InsertShape(rectangle);
	auto groupFrame = group->GetFrame();
	auto rectangleFrame = rectangle->GetFrame();
	

	SECTION("The group does not change frame after addition the empty group")
	{
		auto emptyGroup = make_shared<CCompositeShape>();
		emptyGroup->SetFrame({ 0, 0, 0, 0 });
		std::cout << "Frame: " << group->GetFrame().height << " " << group->GetFrame().width << " " << group->GetFrame().top << " " << group->GetFrame().left << std::endl;

		group->InsertShape(emptyGroup);
		REQUIRE(group->GetFrame().height == 10);
		REQUIRE(group->GetFrame().width == 10);
		REQUIRE(group->GetFrame().top == 10);
		REQUIRE(group->GetFrame().left == 10);
	}

	SECTION("Discoloration of the group changes color in children")
	{
		group->GetFillStyle().SetColor(0x0000ff);
		REQUIRE(group->GetShapeAtIndex(0)->GetFillStyle().GetColor() == group->GetFillStyle().GetColor());
	}

	SECTION("Can set frame with children")
	{
		REQUIRE(groupFrame.top == rectangleFrame.top);
		REQUIRE(groupFrame.left == rectangleFrame.left);
		REQUIRE(groupFrame.height == rectangleFrame.height);
		REQUIRE(groupFrame.width == rectangleFrame.width);

		group->SetFrame({ 500, 150, 50, 50 });
		groupFrame = group->GetFrame();

		groupFrame = group->GetFrame();
		REQUIRE(groupFrame.top == 150);
		REQUIRE(groupFrame.left == 500);
		REQUIRE(groupFrame.height == 50);
		REQUIRE(groupFrame.width == 50);
	}

	SECTION("The group changes frame after addition the empty rectangle")
	{
		auto emptyRectangle = make_shared<CRectangle>(PointD{ 0, 0 }, PointD{ 0, 0 });
		group->InsertShape(emptyRectangle);
		REQUIRE(group->GetShapesCount() == 2);
		REQUIRE(group->GetFrame().height == 20);
		REQUIRE(group->GetFrame().width == 20);
		REQUIRE(group->GetFrame().top == 0);
		REQUIRE(group->GetFrame().left == 0);
	}

	SECTION("Changing the stroke group changes color in children")
	{
		group->GetOutlineStyle().SetColor(0x0000ff);
		REQUIRE(group->GetShapeAtIndex(0)->GetOutlineStyle().GetColor() == group->GetOutlineStyle().GetColor());
	}

	SECTION("Can get shapes count")
	{
		REQUIRE(group->GetShapesCount() == 1);
	}

	SECTION("Shape's frame changes group frame")
	{
		REQUIRE(groupFrame.top == rectangleFrame.top);
		REQUIRE(groupFrame.left == rectangleFrame.left);
		REQUIRE(groupFrame.height == rectangleFrame.height);
		REQUIRE(groupFrame.width == rectangleFrame.width);
	}

	SECTION("Return none when get fill style with different colors")
	{
		newRectangle->GetFillStyle().SetColor(0x0000ff);
		group->InsertShape(newRectangle);
		REQUIRE(group->GetFillStyle().GetColor() == boost::none);
	}

	SECTION("Return none when get outline style with different colors")
	{
		newRectangle->GetOutlineStyle().SetColor(0x0000ff);
		group->InsertShape(newRectangle);
		REQUIRE(group->GetOutlineStyle().GetColor() == boost::none);
	}

	SECTION("Return none when get outline style with different thicknesses")
	{
		newRectangle->GetOutlineStyle().SetThickness(3);
		group->InsertShape(newRectangle);
		REQUIRE(group->GetOutlineStyle().GetThickness() == boost::none);
	}

	SECTION("Return color when get fill style with the same colors")
	{
		newRectangle->GetOutlineStyle().SetColor(0x000000);
		group->InsertShape(newRectangle);
		REQUIRE(group->GetOutlineStyle().GetColor() == newRectangle->GetOutlineStyle().GetColor());
	}

	SECTION("Return color when get outline style with the same thicknesses")
	{
		newRectangle->GetOutlineStyle().SetThickness(2);
		group->InsertShape(newRectangle);
		REQUIRE(group->GetOutlineStyle().GetThickness() == newRectangle->GetOutlineStyle().GetThickness());
	}

	SECTION("Return color when get fill style with the same colors")
	{
		newRectangle->GetFillStyle().SetColor(0x000000);
		group->InsertShape(newRectangle);
		REQUIRE(group->GetFillStyle().GetColor() == newRectangle->GetFillStyle().GetColor());
	}
}