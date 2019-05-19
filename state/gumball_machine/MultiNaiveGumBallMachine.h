﻿#pragma once
#include <boost/format.hpp>
#include <iostream>

namespace naive_multi
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	CGumballMachine(unsigned count, std::ostream& output)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		, m_quartersCount(0)
		, m_output(output)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			m_output << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			m_output << "You inserted a quarter\n";
			m_state = State::HasQuarter;
			InsertAdditionalQuarter();
			break;
		case State::HasQuarter:
			InsertAdditionalQuarter();
			m_output << "You inserted an additional quarter\n";
			break;
		case State::Sold:
			m_output << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			m_output << "Quarter returned\n";
			EjectAdditionalQuarter();
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			m_output << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			m_output << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			if (GetQuartersCount() != 0)
			{
				EjectAdditionalQuarter();
			}
			else
			{
				m_output << "You can't eject, you haven't inserted a quarter yet\n";
			}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			m_output << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			m_output << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			m_output << "You turned...\n";
			m_state = State::Sold;
			ProcessQuarter();
			Dispense();
			break;
		case State::Sold:
			m_output << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count += numBalls;
		m_state = m_count > 0 ? State::NoQuarter : State::SoldOut;
		m_state = (m_quartersCount > 0) ? State::HasQuarter : State::NoQuarter;
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoQuarter) ? "waiting for quarter" : (m_state == State::HasQuarter) ? "waiting for turn of crank" : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Quarters: %3%
Machine is %4%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quartersCount % state).str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			m_output << "A gumball comes rolling out the slot\n";
			--m_count;
			if (m_count == 0)
			{
				m_output << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = (m_quartersCount > 0) ? State::HasQuarter : State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			m_output << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			m_output << "No gumball dispensed\n";
			break;
		}
	}
	void ProcessQuarter()
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}
	void EjectAdditionalQuarter()
	{
		m_output << boost::format(R"(%1% coin%2% returned)") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") << std::endl;
		m_quartersCount = 0;
	}
	unsigned GetQuartersCount() const
	{
		return m_quartersCount;
	}
	void InsertAdditionalQuarter()
	{
		if (m_quartersCount < MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
			m_output << "You inserted an additional quarter\n";
		}
		else
		{
			m_output << "Sorry, you cannot insert more than " << MAX_QUARTERS_COUNT << " guarters :(\n";
		}
	}
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_quartersCount; // Количество монет
	unsigned m_count; // Количество шариков
	State m_state = State::SoldOut;
	std::ostream& m_output;
};
} // namespace naive_multi