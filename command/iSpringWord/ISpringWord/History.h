#pragma once

#include "ICommand_fwd.h"

class CHistory
{
public:
	CHistory();
	~CHistory();

	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command);

private:
	const size_t COMMAND_COUNT = 10;
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};
