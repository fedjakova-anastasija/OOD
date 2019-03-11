#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"
#include <iosfwd>

class CPictureDraft;

struct IShapeFactory;

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory& factory);
	~CDesigner();
	CPictureDraft CreateDraft(std::istream& inputData);

private:
	IShapeFactory& m_factory;
};
