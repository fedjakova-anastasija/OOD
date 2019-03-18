//#include "stdafx.h"
////#include "../libpainter/CCanvas.h"
//#include "../libpainter/CEllipse.h"
//#include "../libpainter/CRectangle.h"
//#include "../libpainter/CRegularPolygon.h"
//#include "../libpainter/CShape.h"
//#include "../libpainter/CTriangle.h"
//#include <boost/test/floating_point_comparison.hpp>
//#include <iostream>
//#include <sstream>
//
//using namespace std;
//
//struct Triangle_
//{
//	stringstream outputStream;
//	//CTestCanvas canvas{ outputStream };
//	CTriangle triangle{ { 0, 0 }, { 3, 0 }, { 0, 4 }, Color::BLACK };
//};
//
//BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
//	BOOST_AUTO_TEST_SUITE(when_created)
//		BOOST_AUTO_TEST_CASE(has_custom_color)
//		{
//			BOOST_CHECK_EQUAL(triangle.GetColor(), Color::BLACK);
//		}
//		/*BOOST_AUTO_TEST_CASE(can_change_color)
//		{
//			triangle.SetColor(Color::RED);
//			BOOST_CHECK_EQUAL(triangle.GetColor(), Color::RED);
//		}*/
//		BOOST_AUTO_TEST_CASE(returns_its_vertices)
//		{
//			CPoint one = triangle.GetVertex1();
//			CPoint two = triangle.GetVertex2();
//			CPoint three = triangle.GetVertex3();
//
//			BOOST_CHECK_EQUAL(one.x, 0);
//			BOOST_CHECK_EQUAL(one.y, 0);
//			BOOST_CHECK_EQUAL(two.x, 3);
//			BOOST_CHECK_EQUAL(two.y, 0);
//			BOOST_CHECK_EQUAL(three.x, 0);
//			BOOST_CHECK_EQUAL(three.y, 4);
//		}
//		/*BOOST_AUTO_TEST_CASE(can_draw_itself_on_canvas)
//		{
//			triangle.Draw(canvas);
//			BOOST_CHECK_EQUAL(outputStream.str(), "Color: green\nLeft top (130, 100)\nwidth:40\nheight:100\n");
//		}*/
//	BOOST_AUTO_TEST_SUITE_END()
//BOOST_AUTO_TEST_SUITE_END()