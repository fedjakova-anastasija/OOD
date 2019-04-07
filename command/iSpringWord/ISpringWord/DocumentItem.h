#pragma once
#include "ConstDocumentItem.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& text);
	
	// Возращает указатель на изображение, либо nullptr, если элемент не является изображжением
	std::shared_ptr<IImage> GetImage();
	// Возращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};
