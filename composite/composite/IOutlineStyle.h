#pragma once
//#include <boost/optional.hpp>
//#include <cstdint>
#include "IStyle.h"
//#include "CommonTypes.h"

//class IOutlineStyle
//{
//public:
//	virtual ~IOutlineStyle() = default;
//
//	virtual boost::optional<bool> IsEnabled() const = 0;
//	virtual void Enable(bool enable) = 0;
//
//	virtual boost::optional<RGBAColor> GetColor() const = 0;
//	virtual void SetColor(RGBAColor color) = 0;
//
//	virtual boost::optional<float> GetThickness() const = 0;
//	virtual void SetThickness(float thickness) = 0;
//	//virtual std::shared_ptr<IStyle> GetStyle(std::shared_ptr<IShape> shape) = 0;
//};

class IOutlineStyle : public IStyle
{
public:
	virtual optional<float> GetThickness() const = 0;
	virtual void SetThickness(float thiсkness) = 0;
};