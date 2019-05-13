#include "MachineState.h"
#include "pch.h"

TEST_CASE("when gumball machine with state has quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	MachineState::CGumballMachine machine(1, out);
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