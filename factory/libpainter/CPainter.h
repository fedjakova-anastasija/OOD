#pragma once
#include "IPainter.h"

class CPainter : public IPainter
{
public:
	CPainter();
	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) override;
};