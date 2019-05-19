#include "Menu.h"
#include "MultiGumballMachine.h"
#include "GumballMachineWithState.h"
#include <ostream>
#include <sstream>

CMenu::CMenu()
	: m_machine(std::make_unique<with_multi_state::CGumballMachine>(5, std::cout))
	//: m_machine(std::make_unique<with_state::CGumballMachine>(5, output))
	, m_exit(false)
{
}

void CMenu::Exit(std::istream&)
{
	m_exit = true;
}

void CMenu::InsertQuarter(std::istream&)
{
	m_machine->InsertQuarter();
}

void CMenu::EjectQuarter(std::istream&)
{
	m_machine->EjectQuarter();
}

void CMenu::ToString(std::istream&)
{
	std::cout << m_machine->ToString();
}

void CMenu::Addition(std::istream& args)
{
	unsigned gumballsCount = 0;
	if (args >> gumballsCount)
	{
		m_machine->Addition(gumballsCount);
	}
	else
	{
		std::cout << "Wrong number of gumballs!" << std::endl;
	}
}

void CMenu::TurnCrank(std::istream&)
{
	m_machine->TurnCrank();
}

void CMenu::Help(std::istream&)
{
	std::cout << "HELPER:" << std::endl;
	for (auto& command : COMMANDS)
	{
		std::cout << command.title << std::endl;
	}
}

void CMenu::Run()
{
	Help(std::cin);
	std::string command;
	while (!m_exit && (std::cout << "-->") && getline(std::cin, command))
	{
		std::istringstream line(command);
		std::string title;
		line >> title;

		auto it = std::find_if(COMMANDS.cbegin(), COMMANDS.cend(), [&](const Action& action) {
			return action.title == title;
		});
		if (it == COMMANDS.end())
		{
			std::cout << "Wrong command!" << std::endl;
			continue;
		}
		it->command(line);
	}
}