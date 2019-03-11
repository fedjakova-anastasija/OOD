// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/CCanvas.h"
#include "../libpainter/CDesigner.h"
#include "../libpainter/CModernCanvas.h"
#include "../libpainter/CShapeFactory.h"
#include "../libpainter/Config.h"

void Info()
{
	std::cout << "-> Create an ellipse: " << CREATE_ELLIPSE << " <center.x> <center.y> <horizontal radius> <vertical radius> <color>" << std::endl
			  << "-> Create a rectangle: " << CREATE_RECTANGLE << " <leftTop.x> <leftTop.y> <rightBottom.x> <rightBottom.y> <color>" << std::endl
			  << "-> Create a triangle: " << CREATE_TRIANGLE << " <first.x> <first.y> <second.x> <second.y> <third.x> <third.y> <color>" << std::endl
			  << "-> Create a regylar polygon: " << CREATE_REGULAR_POLYGON << " <center.x> <center.y> <radius> <vertex count> <color>" << std::endl
			  << "-> Color: " << "red, green, blue, black, pink, yellow" << std::endl;
}

int main()
{
	Info();
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CPictureDraft pictureDraft = designer.CreateDraft(std::cin);

	return 0;
}
