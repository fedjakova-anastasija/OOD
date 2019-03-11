// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/CCanvas.h"
#include "../libpainter/CDesigner.h"
#include "../libpainter/CModernCanvas.h"
#include "../libpainter/CShapeFactory.h"

int main()
{
	std::cout << "Enter <info> to get valid input" << std::endl;
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CPictureDraft pictureDraft = designer.CreateDraft(std::cin);

	return 0;
}
