#include "stdafx.h"
#include "CPainter.h"

CPainter::CPainter()
{
}

void CPainter::DrawPicture(const CPictureDraft& draft, ICanvas& canvas)
{
	for (auto it = draft.begin(); it != draft.end(); ++it)
	{
		it->Draw(canvas);
	}
}