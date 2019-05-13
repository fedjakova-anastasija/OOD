#include "MachineState.h"
#include "pch.h"

TEST_CASE("when gumball machine with state has sold out state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	MachineState::CGumballMachine machine(1, out);
	with_state::CSoldOutState soldStateMachine(machine, out);

	SECTION("can not insert quarter")
	{
		soldStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("can not eject a quarter")
	{
		soldStateMachine.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
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

	SECTION("shows delivering a gumball message")
	{
		auto str = soldStateMachine.ToString();
		REQUIRE(str == "sold out");
	}
}