#pragma once
#include "MultiGumBallMachine.h"

class CMenu
{
public:
	CMenu();
	void Run();

private:
	bool m_exit;
	std::unique_ptr<with_multi_state::CGumballMachine> m_machine;
	using Command = std::function<void(std::istream& args)>;

	void InsertQuarter(std::istream&);
	void EjectQuarter(std::istream&);
	void TurnCrank(std::istream&);
	void ToString(std::istream&);
	void Addition(std::istream&);
	void Exit(std::istream&);
	void Help(std::istream&);

	struct Action
	{
		Action(const std::string& title, const Command& command)
			: title(title)
			, command(command)
		{
		}

		std::string title;
		Command command;
	};

	const std::vector<Action> COMMANDS = {
		{ "InsertQuarter", std::bind(&CMenu::InsertQuarter, this, std::placeholders::_1) },
		{ "EjectQuarter", std::bind(&CMenu::EjectQuarter, this, std::placeholders::_1) },
		{ "ToString", std::bind(&CMenu::ToString, this, std::placeholders::_1) },
		{ "TurnCrank", std::bind(&CMenu::TurnCrank, this, std::placeholders::_1) },
		{ "Addition", std::bind(&CMenu::Addition, this, std::placeholders::_1) },
		{ "Help", std::bind(&CMenu::Help, this, std::placeholders::_1) },
		{ "Exit", std::bind(&CMenu::Exit, this, std::placeholders::_1) }
	};
};