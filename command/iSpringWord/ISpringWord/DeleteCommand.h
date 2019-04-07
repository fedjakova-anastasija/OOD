#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CDeleteCommand : public CAbstractCommand
{
public:
	CDeleteCommand(std::vector<CDocumentItem>& items, size_t index);
	~CDeleteCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem>& m_items;
	std::shared_ptr<CDocumentItem> m_item;
	size_t m_index;
};
