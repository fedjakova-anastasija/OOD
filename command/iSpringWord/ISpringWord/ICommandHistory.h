#pragma once
#include "ICommand_fwd.h"

class ICommandHistory
{
public:
	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;

	virtual ~ICommandHistory() = default;
};
