#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CAddParagraphCommand : public CAbstractCommand
{
public:
	CAddParagraphCommand(std::shared_ptr<IParagraph>&& text, std::vector<CDocumentItem>& items, boost::optional<size_t> pos);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	void CheckPos();
	std::vector<CDocumentItem>& m_items;
	boost::optional<size_t> m_pos;
	std::shared_ptr<IParagraph> m_text;
};
