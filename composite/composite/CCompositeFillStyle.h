#pragma once
#include "IStyle.h"

typedef std::function<void(std::function<void(IStyle&)>)> FillStyleEnumerator;

class CCompositeFillStyle : public IStyle
{
public:
	CCompositeFillStyle(FillStyleEnumerator&& enumerator);

	optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	FillStyleEnumerator m_enumerator;
};