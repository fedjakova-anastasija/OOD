#include "MultiMachineState.h"
#include "pch.h"

TEST_CASE("when multi gumball machine has sold state, it ", "[CSoldStateTests]")
{
	std::stringstream out;
	MultiMachineState::CGumballMachine machine(1, out);
	with_multi_state::CSoldState soldStateMachine(machine, out);

	SECTION("can not insert quarter")
	{
		soldStateMachine.InsertQuarter();
		REQUIRE(out.str() == "Please wait, we're already giving you a gumball\n");
	}

	SECTION("can not eject a quarter")
	{
		soldStateMachine.EjectQuarter();
		REQUIRE(out.str() == "Sorry you already turned the crank\n");
	}

	SECTION("can not turn a crank")
	{
		soldStateMachine.TurnCrank();
		REQUIRE(out.str() == "Turning twice doesn't get you another gumball\n");
	}

	SECTION("can not dispense")
	{
		std::stringstream out;
		MultiMachineState::CGumballMachine machine(0, out);
		with_multi_state::CSoldState soldStateMachine(machine, out);
		soldStateMachine.Dispense();
		REQUIRE(out.str() == "Oops, out of gumballs\n");
	}

	SECTION("can dispense")
	{
		soldStateMachine.Dispense();
		REQUIRE(out.str() == "");
	}

	SECTION("can not add gumballs")
	{
		soldStateMachine.Addition(1);
		REQUIRE(out.str() == "Sorry, you cannot add the gumballs when the machine is working :(\n");
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = soldStateMachine.ToString();
		REQUIRE(str == "delivering a gumball");
	}
}