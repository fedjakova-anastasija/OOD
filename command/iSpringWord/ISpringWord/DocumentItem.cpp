#include "stdafx.h"
#include "DocumentItem.h"

CDocumentItem::CDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& paragraph)
	: CConstDocumentItem(image, paragraph)
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return std::shared_ptr<IImage>();
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return std::shared_ptr<IParagraph>();
}
