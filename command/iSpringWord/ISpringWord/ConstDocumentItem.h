#pragma once
#include "IImage.h"
#include "IParagraph.h"
#include <memory>
#include <string>

class CConstDocumentItem
{
public:
	CConstDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& text);

	// Возвращает указатель на константное изображение, либо nullptr
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_text;
};
