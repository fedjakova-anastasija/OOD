#pragma once
//#include "ICompositeStyle.h"
//#include "IShape.h"
#include "IStyle.h"
//#include "IFillStyle.h"

//class CFillStyle : public ICompositeStyle
//{
//public:
//	std::shared_ptr<IStyle> GetStyle(std::shared_ptr<IShape> shape) override;
//};

class CFillStyle : public IStyle
{
public:
	CFillStyle(bool isEnabled, RGBAColor color);

	virtual optional<bool> IsEnabled()const override;
	virtual void Enable(bool enable) override;

	virtual optional<RGBAColor> GetColor()const override;
	virtual void SetColor(RGBAColor color) override;

	//std::shared_ptr<IStyle> GetStyle(std::shared_ptr<IShape> shape) override;
private:
	bool m_isEnabled;
	RGBAColor m_color;
};