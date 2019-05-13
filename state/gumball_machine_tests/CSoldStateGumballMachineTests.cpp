#include "MachineState.h"
#include "pch.h"

TEST_CASE("when gumball machine with state has sold state, it ", "[CSoldStateGumBallMachineTests]")
{
	std::stringstream out;
	MachineState::CGumballMachine machine(1, out);
	with_state::CSoldState soldStateMachine(machine, out);

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
		MachineState::CGumballMachine machine(0, out);
		with_state::CSoldState soldStateMachine(machine, out);
		soldStateMachine.Dispense();
		REQUIRE(out.str() == "Oops, out of gumballs\n");
	}

	SECTION("can dispense")
	{
		soldStateMachine.Dispense();
		REQUIRE(out.str() == "");
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = soldStateMachine.ToString();
		REQUIRE(str == "delivering a gumball");
	}
}