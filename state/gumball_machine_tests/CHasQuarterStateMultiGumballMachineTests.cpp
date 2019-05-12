#include "../gumball_machine/MultiGumBallMachine.h"
#include "pch.h"

namespace CHasQuarterStateTests
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
} // namespace CHasQuarterStateTests

TEST_CASE("when multi gumball machine has quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	CHasQuarterStateTests::CGumballMachine machine(1, out);
	with_multi_state::CHasQuarterState hasQuarterStateMachine(machine, out);

	SECTION("can not insert quarter when machine has limit quarters")
	{
		hasQuarterStateMachine.InsertQuarter();
		hasQuarterStateMachine.InsertQuarter();
		hasQuarterStateMachine.InsertQuarter();
		hasQuarterStateMachine.InsertQuarter();
		hasQuarterStateMachine.InsertQuarter();
		hasQuarterStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert another quarter\n");
	}

	SECTION("can insert quarter when machine hasn't limit quarters")
	{
		hasQuarterStateMachine.InsertQuarter();
		REQUIRE(out.str() == "");
	}

	SECTION("can eject a quarter")
	{
		hasQuarterStateMachine.EjectQuarter();
		REQUIRE(out.str() == "Quarter returned\n");
	}

	SECTION("can turn a crank")
	{
		hasQuarterStateMachine.TurnCrank();
		REQUIRE(out.str() == "You turned...\n");
	}

	SECTION("can not dispense")
	{
		hasQuarterStateMachine.Dispense();
		REQUIRE(out.str() == "No gumball dispensed\n");
	}

	SECTION("can add gumballs")
	{
		REQUIRE(machine.GetBallCount() == 1);
		hasQuarterStateMachine.Addition(1);
		REQUIRE(machine.GetBallCount() == 2);
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = hasQuarterStateMachine.ToString();
		REQUIRE(str == "waiting for turn of crank");
	}
}