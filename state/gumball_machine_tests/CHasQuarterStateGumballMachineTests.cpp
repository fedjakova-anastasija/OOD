#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

namespace CHasQuarterStateTests
{
class CGumballMachine : public with_state::IGumballMachine
{
public:
	CGumballMachine(unsigned count, std::stringstream& output)
		: m_count(count)
		, m_out(output){};

	unsigned GetBallCount() const override
	{
		return m_count;
	};

private:
	void ReleaseBall() override{};

	void SetSoldOutState() override{};
	void SetNoQuarterState() override{};
	void SetSoldState() override{};
	void SetHasQuarterState() override{};

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_count = 0;
	unsigned m_quartersCount = 0;
	with_state::IState* m_state;
	std::stringstream& m_out;
};
} // namespace CHasQuarterStateTests

TEST_CASE("when gumball machine with state has quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	CHasQuarterStateTests::CGumballMachine machine(1, out);
	with_state::CHasQuarterState hasQuarterStateMachine(machine, out);

	SECTION("can not insert quarter")
	{
		hasQuarterStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert another quarter\n");
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

	SECTION("shows delivering a gumball message")
	{
		auto str = hasQuarterStateMachine.ToString();
		REQUIRE(str == "waiting for turn of crank");
	}
}