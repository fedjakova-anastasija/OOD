#include "MultiMachineState.h"
#include "pch.h"

TEST_CASE("when multi gumball machine has sold out state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	MultiMachineState::CGumballMachine machine(1, out);
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