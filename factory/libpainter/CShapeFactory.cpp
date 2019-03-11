#include "stdafx.h"
#include "CShapeFactory.h"
#include "CCanvas.h"
#include "CDesigner.h"
#include "Config.h"

CShapeFactory::CShapeFactory()
	: m_action({ { CREATE_ELLIPSE, bind(&CShapeFactory::CreateEllipse, this, std::placeholders::_1) },
		  { CREATE_RECTANGLE, bind(&CShapeFactory::CreateRectangle, this, std::placeholders::_1) },
		  { CREATE_TRIANGLE, bind(&CShapeFactory::CreateTriangle, this, std::placeholders::_1) },
		  { CREATE_REGULAR_POLYGON, bind(&CShapeFactory::CreateRegularPolygon, this, std::placeholders::_1) } })
{
}

void CShapeFactory::Info()
{
	std::cout << "-> Create an ellipse: " << CREATE_ELLIPSE << " <center.x> <center.y> <horizontal radius> <vertical radius> <color>" << std::endl
			  << "-> Create a rectangle: " << CREATE_RECTANGLE << " <leftTop.x> <leftTop.y> <rightBottom.x> <rightBottom.y> <color>" << std::endl
			  << "-> Create a triangle: " << CREATE_TRIANGLE << " <first.x> <first.y> <second.x> <second.y> <third.x> <third.y> <color>" << std::endl
			  << "-> Create a regylar polygon: " << CREATE_REGULAR_POLYGON << " <center.x> <center.y> <radius> <vertex count> <color>" << std::endl
			  << "-> Color: "
			  << "red, green, blue, black, pink, yellow" << std::endl;
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream stream(description);
	std::string action;
	stream >> action;

	if (action == "info")
	{
		Info();
	}

	auto it = m_action.find(action);
	if (it != m_action.end())
	{
		return it->second(stream);
	}
	else
	{
		throw std::invalid_argument("Wrong command name!\nEnter <info> to get valid input\n");
	}
}

std::unique_ptr<CTriangle> CShapeFactory::CreateTriangle(std::istringstream& args) const
{
	CPoint first;
	CPoint second;
	CPoint third;

	Color color;

	if (args >> first.x >> first.y >> second.x >> second.y >> third.x >> third.y >> color)
	{
		return std::make_unique<CTriangle>(first, second, third, color);
	}
	else
	{
		throw std::invalid_argument("Failed to create an triangle\n");
	}
}

std::unique_ptr<CRectangle> CShapeFactory::CreateRectangle(std::istringstream& args) const
{
	Color color;
	CPoint leftTop;
	CPoint rightBottom;

	if (args >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y >> color)
	{
		return std::make_unique<CRectangle>(leftTop, rightBottom, color);
	}
	else
	{
		throw std::invalid_argument("Failed to create an rectangle\n");
	}
}

std::unique_ptr<CEllipse> CShapeFactory::CreateEllipse(std::istringstream& args) const
{
	Color color;
	CPoint center;
	double horizontalRadius;
	double verticalRadius;

	if (args >> center.x >> center.y >> horizontalRadius >> verticalRadius >> color)
	{
		return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, color);
	}
	else
	{
		throw std::invalid_argument("Failed to create an ellipse\n");
	}
}

std::unique_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(std::istringstream& args) const
{
	Color color;
	CPoint center;
	double radius;
	unsigned vertexCount;

	if (args >> center.x >> center.y >> radius >> vertexCount >> color)
	{
		return std::make_unique<CRegularPolygon>(center, radius, vertexCount, color);
	}
	else
	{
		throw std::invalid_argument("Failed to create a regular polygon\n");
	}
}
