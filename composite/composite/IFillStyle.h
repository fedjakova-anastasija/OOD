#pragma once
#include <boost/optional.hpp>
#include <cstdint>

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;

	virtual boost::optional<bool> IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	//virtual std::shared_ptr<IStyle> GetStyle(std::shared_ptr<IShape> shape) = 0;
};