#include "../ISpringWord/stdafx.h"
#include "DocumentItem.h"

CDocumentItem::CDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& text)
	: CConstDocumentItem(image, text)
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_text;
}
