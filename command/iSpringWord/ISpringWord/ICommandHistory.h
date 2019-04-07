#pragma once
//class ICommand;
#include "ICommand_fwd.h"

class ICommandHistory
{
public:
	virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;

	virtual ~ICommandHistory() = default;
};
