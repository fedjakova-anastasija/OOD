#pragma once
#include "CEllipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CShape.h"
#include "CTriangle.h"
#include "IShapeFactory.h"
#include <functional>

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	~CShapeFactory() = default;
	std::unique_ptr<CShape> CreateShape(const std::string& description) override;

private:
	typedef std::map<std::string, std::function<std::unique_ptr<CShape>(std::istringstream& stream)>> ActionMap;

	std::unique_ptr<CEllipse> CreateEllipse(std::istringstream& stream) const;
	std::unique_ptr<CRectangle> CreateRectangle(std::istringstream& stream) const;
	std::unique_ptr<CTriangle> CreateTriangle(std::istringstream& stream) const;
	std::unique_ptr<CRegularPolygon> CreateRegularPolygon(std::istringstream& stream) const;

	const ActionMap m_actionMap;
};
