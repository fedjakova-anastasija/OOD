#include "stdafx.h"
#include "DeleteCommand.h"

CDeleteCommand::CDeleteCommand(std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
	, m_index(index)
	, m_item(std::make_shared<CDocumentItem>(nullptr, nullptr))
{
}

CDeleteCommand::~CDeleteCommand()
{
	if (m_executed && m_item->GetImage())
	{
		boost::system::error_code errorCode;
		boost::filesystem::remove(m_item->GetImage()->GetPath(), errorCode);
	}
}

void CDeleteCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_index);
}

void CDeleteCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, *m_item);
}
