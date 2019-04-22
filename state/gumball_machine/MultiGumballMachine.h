#pragma once
#include <boost\format.hpp>
#include <iostream>

namespace with_multi_state
{

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Addition(unsigned gumballsCount) = 0;
	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;

	virtual void AddGumballs(unsigned gumballsCount) = 0;
	virtual void ProcessQuarter() = 0;
	virtual void InsertAdditionalQuarter() = 0;
	virtual void EjectAdditionalQuarter() = 0;
	virtual unsigned GetQuartersCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual void Addition(unsigned gumballsCount) = 0;

	virtual ~IGumballMachine() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetQuartersCount() != 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
	}
	void Addition(unsigned gumballsCount) override
	{
		//m_gumballMachine.AddGumballs(gumballsCount);
		std::cout << "Sorry, you cannot add the gumballs then the machine is workink :(\n ";
	}

	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.GetQuartersCount() != 0)
		{
			m_gumballMachine.EjectAdditionalQuarter();
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
		}
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}

	void Addition(unsigned gumballsCount) override
	{
		m_gumballMachine.AddGumballs(gumballsCount);
		if (m_gumballMachine.GetQuartersCount() > 0)
		{
			m_gumballMachine.SetHasQuarterState();
		}
		else
		{
			if (m_gumballMachine.GetBallCount() > 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetSoldOutState();
			}
		}
	}
	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.GetQuartersCount() < MAX_QUARTERS_COUNT)
		{
			m_gumballMachine.InsertAdditionalQuarter();
		}
		else
		{
			std::cout << "You can't insert another quarter\n";
		}
	}
	void EjectQuarter() override
	{
		std::cout << "Quarter returned\n";
		m_gumballMachine.EjectAdditionalQuarter();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.ProcessQuarter();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	void Addition(unsigned gumballsCount) override
	{
		m_gumballMachine.AddGumballs(gumballsCount);
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	IGumballMachine& m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.InsertAdditionalQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	void Addition(unsigned gumballsCount) override
	{
		m_gumballMachine.AddGumballs(gumballsCount);
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	IGumballMachine& m_gumballMachine;
};

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_quartersCount = 0;
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	void Addition(unsigned gumballsCount)
	{
		m_state->Addition(gumballsCount);
	}
	std::string ToString() const
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quarters: %3%
Machine is %4%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quartersCount % m_state->ToString()).str();
	}

private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}

	unsigned GetQuartersCount() const override
	{
		return m_quartersCount;
	}
	virtual void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	void InsertAdditionalQuarter()
	{
		if (m_quartersCount < MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
			std::cout << "You inserted an additional quarter\n";
		}
		else
		{
			std::cout << "Sorry, you cannot insert more than " << MAX_QUARTERS_COUNT << " guarters :(\n";
		}
	}
	void ProcessQuarter() override
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}
	void AddGumballs(unsigned gumballsCount) override
	{
		m_count += gumballsCount;
	}
	void EjectAdditionalQuarter() override
	{
		m_quartersCount = 0;
		std::cout << boost::format(R"(%1% quarter%2% returned)") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") << std::endl;
	}
	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_count = 0;
	unsigned m_quartersCount = 0;
	const unsigned MAX_QUARTERS_COUNT = 5;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
}; // namespace with_multi_state

} // namespace with_multi_state
