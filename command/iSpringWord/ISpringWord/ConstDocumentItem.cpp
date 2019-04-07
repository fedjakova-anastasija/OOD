#include "stdafx.h"
#include "ConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& text)
	: m_image(image)
	, m_text(text)
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_text;
}
