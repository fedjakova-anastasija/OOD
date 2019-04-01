#include "stdafx.h"
#include "ConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& paragraph)
	: m_image(image)
	, m_paragraph(paragraph)
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return nullptr;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return nullptr;
}
