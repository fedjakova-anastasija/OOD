#include "MultiMachineState.h"
#include "pch.h"

TEST_CASE("when multi gumball machine has quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	MultiMachineState::CGumballMachine machine(1, out);
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