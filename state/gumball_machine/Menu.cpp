#include "Menu.h"
#include "MultiGumballMachine.h"
#include "GumballMachineWithState.h"
#include <sstream>

CMenu::CMenu(std::stringstream& output)
	: m_machine(std::make_unique<with_multi_state::CGumballMachine>(5, output))
	//: m_machine(std::make_unique<with_state::CGumballMachine>(5, output))
	, m_exit(false)
	, m_out(output)
{
}

void CMenu::Exit(std::istream&)
{
	m_exit = true;
}

void CMenu::InsertQuarter(std::istream&)
{
	m_out.str("");
	m_machine->InsertQuarter();
	std::cout << m_out.str();
}

void CMenu::EjectQuarter(std::istream&)
{
	m_out.str("");
	m_machine->EjectQuarter();
	std::cout << m_out.str();
}

void CMenu::ToString(std::istream&)
{
	m_out.str("");
	std::cout << m_machine->ToString();
	std::cout << m_out.str();
}

void CMenu::Addition(std::istream& args)
{
	m_out.str("");
	unsigned gumballsCount = 0;
	if (args >> gumballsCount)
	{
		m_machine->Addition(gumballsCount);
	std::cout << m_out.str();
	}
	else
	{
		std::cout << "Wrong number of gumballs!" << std::endl;
		m_out.str("Wrong number of gumballs!");
	}
}

void CMenu::TurnCrank(std::istream&)
{
	m_out.str("");
	m_machine->TurnCrank();
	std::cout << m_out.str();
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