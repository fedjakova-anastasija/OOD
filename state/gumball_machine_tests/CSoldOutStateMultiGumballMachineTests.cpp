#include "../gumball_machine/MultiGumBallMachine.h"
#include "pch.h"

namespace CSoldOutStateTests
{
class CGumballMachine : public with_multi_state::IGumballMachine
{
public:
	CGumballMachine(unsigned count, std::stringstream& output)
		: m_count(count)
		, m_out(output){};

	void InsertAdditionalQuarter() override
	{
		if (m_quartersCount != MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
		}
	};
	void Addition(unsigned count) override
	{
		m_count += count;
	};

	unsigned GetBallCount() const override
	{
		return m_count;
	};

	unsigned GetQuartersCount() const override
	{
		return m_quartersCount;
	};

private:
	void EjectAdditionalQuarter() override
	{
		m_quartersCount = 0;
	}

	void AddGumballs(unsigned gumballsCount) override
	{
		m_count += gumballsCount;
	}

	void ReleaseBall() override{};

	void ProcessQuarter() override
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}

	void SetSoldOutState() override{};
	void SetNoQuarterState() override{};
	void SetSoldState() override{};
	void SetHasQuarterState() override{};

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_count = 0;
	unsigned m_quartersCount = 0;
	with_multi_state::IState* m_state;
	std::stringstream& m_out;
};
} // namespace CSoldOutStateTests

TEST_CASE("when multi gumball machine has sold out state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	CSoldOutStateTests::CGumballMachine machine(1, out);
	with_multi_state::CSoldOutState soldStateMachine(machine, out);

	SECTION("can not insert quarter")
	{
		soldStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("can not eject a quarter when machine has no quarter")
	{
		soldStateMachine.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
	}

	SECTION("can eject a quarter when machine has quarter")
	{		
		machine.InsertAdditionalQuarter();
		soldStateMachine.EjectQuarter();
		REQUIRE(machine.GetQuartersCount() == 0);
		REQUIRE(out.str() == "");
	}

	SECTION("can not turn a crank")
	{
		soldStateMachine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no gumballs\n");
	}

	SECTION("can not dispense")
	{
		soldStateMachine.Dispense();
		REQUIRE(out.str() == "No gumball dispensed\n");
	}

	SECTION("can add gumballs")
	{
		REQUIRE(machine.GetBallCount() == 1);
		soldStateMachine.Addition(1);
		REQUIRE(machine.GetBallCount() == 2);
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = soldStateMachine.ToString();
		REQUIRE(str == "sold out");
	}
}