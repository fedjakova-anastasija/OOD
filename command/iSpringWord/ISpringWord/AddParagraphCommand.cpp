#include "../ISpringWord/stdafx.h"
#include "AddParagraphCommand.h"
#include "Paragraph.h"

CAddParagraphCommand::CAddParagraphCommand(std::shared_ptr<IParagraph>&& text, std::vector<CDocumentItem>& items, boost::optional<size_t> pos)
	: m_items(items)
	, m_pos(pos)
	, m_text(text)
{
}

void CAddParagraphCommand::CheckPos()
{
	if (m_pos > m_items.size())
	{
		throw std::invalid_argument("Wrong position!");
	}
}

void CAddParagraphCommand::DoExecute()
{
	CheckPos();
	if (m_pos != boost::none)
	{
		m_items.emplace(m_items.begin() + m_pos.get(), CDocumentItem(nullptr, m_text));
	}
	else
	{
		m_items.emplace_back(CDocumentItem(nullptr, m_text));
	}	
}

void CAddParagraphCommand::DoUnexecute()
{
	if (m_pos != boost::none)
	{
		m_items.erase(m_items.begin() + m_pos.get());
	}
	else
	{
		m_items.pop_back();
	}
}
