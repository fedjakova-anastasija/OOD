#include "stdafx.h"
#include "../libpainter/CEllipse.h"

#include "../libpainter/CRectangle.h"

#include "../libpainter/CRegularPolygon.h"
#include "../libpainter/CTriangle.h"

namespace
{
class CTestCanvas : public ICanvas
{
public:
	CTestCanvas(std::stringstream& stream)
		: m_stream(stream)
	{
	}

	void SetColor(const Color& color) override
	{
		m_color = color;
		m_stream << "Color: " << m_color << std::endl;
	}
	void DrawLine(const CPoint& /*from*/, const CPoint& /*to*/) override
	{
		m_stream << "DrawLine" << std::endl;
	}
	void DrawEllipse(double left, double top, double width, double height) override
	{
		m_stream << "Left top (" << left << ", " << top << ")" << std::endl;
		m_stream << "width:" << width << std::endl;
		m_stream << "height:" << height << std::endl;
	}

private:
	std::stringstream& m_stream;
	Color m_color;
};

struct Ellipse_
{
	const CPoint expectedPoint{ 150, 150 };
	const double expectedHorizontalRadius = 20;
	const double expectedVerticalRadius = 50;
	const Color expectedColor = Color::GREEN;
	const CEllipse ellipse;
	Ellipse_()
		: ellipse(expectedPoint, expectedHorizontalRadius, expectedVerticalRadius, expectedColor)
	{
	}
};

bool operator==(const CPoint& first, const CPoint& second)
{
	return first.x == second.x && first.y == second.y;
}

} // namespace

BOOST_FIXTURE_TEST_SUITE(Ellipse, Ellipse_)

	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK(ellipse.GetCenter() == expectedPoint);
	}

	BOOST_AUTO_TEST_CASE(has_a_horizontal_radius)
	{
		BOOST_CHECK_EQUAL(ellipse.GetHorizontalRadius(), expectedHorizontalRadius);
	}

	BOOST_AUTO_TEST_CASE(has_a_vertical_radius)
	{
		BOOST_CHECK_EQUAL(ellipse.GetVerticalRadius(), 50);
	}

	BOOST_AUTO_TEST_CASE(has_a_color)
	{
		BOOST_CHECK_EQUAL(ellipse.GetColor(), expectedColor);
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas)
	{
		std::stringstream strm;
		CTestCanvas canvas(strm);
		ellipse.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), "Color: green\nLeft top (130, 100)\nwidth:40\nheight:100\n");
	}

BOOST_AUTO_TEST_SUITE_END()

namespace
{
struct Rectangle_
{
	const CPoint expectedLeftTop{ 10, 10 };
	const CPoint expectedRightBottom{ 150, 150 };

	const Color expectedColor = Color::PINK;
	const CRectangle rectangle;
	Rectangle_()
		: rectangle(expectedLeftTop, expectedRightBottom, expectedColor)
	{
	}
};

} // namespace
BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)

	BOOST_AUTO_TEST_CASE(has_a_leftTop)
	{
		BOOST_CHECK(rectangle.GetLeftTop() == expectedLeftTop);
	}

	BOOST_AUTO_TEST_CASE(has_a_rightBottom)
	{
		BOOST_CHECK(rectangle.GetRightBottom() == expectedRightBottom);
	}

	BOOST_AUTO_TEST_CASE(has_a_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetColor(), expectedColor);
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas)
	{
		std::stringstream strm;
		CTestCanvas canvas(strm);
		rectangle.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), "Color: pink\nDrawLine\nDrawLine\nDrawLine\nDrawLine\n");
	}

BOOST_AUTO_TEST_SUITE_END()

namespace
{
struct Triangle_
{
	const CPoint expectedFirst{ 10, 20 };
	const CPoint expectedSecond{ 40, 80 };
	const CPoint expectedThird{ 20, 40 };

	const Color expectedColor = Color::PINK;
	const CTriangle triangle;
	Triangle_()
		: triangle(expectedFirst, expectedSecond, expectedThird, expectedColor)
	{
	}
};

} // namespace

BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)

	BOOST_AUTO_TEST_CASE(has_are_vertexes)
	{
		BOOST_CHECK(triangle.GetVertex1() == expectedFirst);
		BOOST_CHECK(triangle.GetVertex2() == expectedSecond);
		BOOST_CHECK(triangle.GetVertex3() == expectedThird);
	}

	BOOST_AUTO_TEST_CASE(has_a_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetColor(), expectedColor);
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas)
	{
		std::stringstream strm;
		CTestCanvas canvas(strm);
		triangle.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), "Color: pink\nDrawLine\nDrawLine\nDrawLine\n");
	}

BOOST_AUTO_TEST_SUITE_END()

namespace
{
struct RegularPolygon_
{
	const CPoint expectedCenter{ 100, 100 };
	const double expectedRadius = 40.f;
	const unsigned expectedVertexCount = 6;

	const Color expectedColor = Color::PINK;
	const CRegularPolygon regularPolygon;
	RegularPolygon_()
		: regularPolygon(expectedCenter, expectedRadius, expectedVertexCount, expectedColor)
	{
	}
};

} // namespace

BOOST_FIXTURE_TEST_SUITE(RegularPolygon, RegularPolygon_)

	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK(regularPolygon.GetCenter() == expectedCenter);
	}

	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(regularPolygon.GetRadius(), expectedRadius);
	}
	BOOST_AUTO_TEST_CASE(has_a_vertex_count)
	{
		BOOST_CHECK_EQUAL(regularPolygon.GetVertexCount(), expectedVertexCount);
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas)
	{
		std::stringstream strm;
		CTestCanvas canvas(strm);
		regularPolygon.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), "Color: pink\nDrawLine\nDrawLine\nDrawLine\nDrawLine\nDrawLine\nDrawLine\n");
	}

BOOST_AUTO_TEST_SUITE_END()
