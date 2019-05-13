#include "MachineState.h"
#include "pch.h"

TEST_CASE("when gumball machine with state has no quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	MachineState::CGumballMachine machine(1, out);
	with_state::CNoQuarterState noQuarterStateMachine(machine, out);

	SECTION("can insert quarter")
	{
		noQuarterStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
	}
	
	SECTION("can not eject a quarter")
	{
		noQuarterStateMachine.EjectQuarter();
		REQUIRE(out.str() == "You haven't inserted a quarter\n");
	}

	SECTION("can turn a crank")
	{
		noQuarterStateMachine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no quarter\n");
	}

	SECTION("can not dispense")
	{
		noQuarterStateMachine.Dispense();
		REQUIRE(out.str() == "You need to pay first\n");
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = noQuarterStateMachine.ToString();
		REQUIRE(str == "waiting for quarter");
	}
}