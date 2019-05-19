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
	CSoldState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}
	void InsertQuarter() override
	{
		m_output << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		m_output << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		m_output << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			m_output << "Oops, out of gumballs\n";
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
	void Addition(unsigned /*gumballsCount*/) override
	{
		//m_gumballMachine.AddGumballs(gumballsCount);
		m_output << "Sorry, you cannot add the gumballs when the machine is working :(\n";
	}

	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_output;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}

	void InsertQuarter() override
	{
		m_output << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.GetQuartersCount() != 0)
		{
			m_gumballMachine.EjectAdditionalQuarter();
			//m_gumballMachine.SetNoQuarterState();
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			m_output << "You can't eject, you haven't inserted a quarter yet\n";
		}
	}
	void TurnCrank() override
	{
		m_output << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		m_output << "No gumball dispensed\n";
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
			/*else
			{
				m_gumballMachine.SetSoldOutState();
			}*/
		}
	}
	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_output;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
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
			m_output << "You can't insert another quarter\n";
		}
	}
	void EjectQuarter() override
	{
		m_output << "Quarter returned\n";
		m_gumballMachine.EjectAdditionalQuarter();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		m_output << "You turned...\n";
		m_gumballMachine.ProcessQuarter();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		m_output << "No gumball dispensed\n";
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
	std::ostream& m_output;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}

	void InsertQuarter() override
	{
		//m_output << "You inserted a quarter\n";
		m_gumballMachine.InsertAdditionalQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		m_output << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		m_output << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		m_output << "You need to pay first\n";
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
	std::ostream& m_output;
};

class CGumballMachine : public IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls, std::ostream& output)
		: m_soldState(*this, output)
		, m_soldOutState(*this, output)
		, m_noQuarterState(*this, output)
		, m_hasQuarterState(*this, output)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
		, m_output(output)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
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
			m_output << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
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
		m_output << boost::format(R"(%1% quarter%2% returned)") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") << std::endl;
		m_quartersCount = 0;
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
	std::ostream& m_output;
}; // namespace with_multi_state

} // namespace with_multi_state
