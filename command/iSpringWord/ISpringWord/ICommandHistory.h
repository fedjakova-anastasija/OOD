#pragma once
class ICommand;

class ICommandHistory
{
public:
	virtual void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command) = 0;
	virtual ~ICommandHistory() = default;
};
