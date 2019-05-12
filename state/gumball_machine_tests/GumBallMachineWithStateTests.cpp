#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

std::string MachineState(unsigned count, std::string state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % count % (count != 1 ? "s" : "") % state).str();
}

TEST_CASE("Gumball machine with state ")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5, strm };

	SECTION("can set the correct initial state.")
	{
		REQUIRE(machine.ToString() == MachineState(5, "waiting for quarter"));
	}

	SECTION("cannot change the state if the crank is turned without a quarter.")
	{
		machine.TurnCrank();
		REQUIRE(machine.ToString() == MachineState(5, "waiting for quarter"));
	}

	SECTION("can change the state if you insert a quarter.")
	{
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == MachineState(5, "waiting for turn of crank"));
	}

	SECTION("cannot change the state if you insert and then eject the quarter.")
	{
		machine.InsertQuarter();
		machine.EjectQuarter();
		REQUIRE(machine.ToString() == MachineState(5, "waiting for quarter"));
	}

	SECTION("cannot eject a quarter if you haven't inserted it.")
	{
		machine.EjectQuarter();
		REQUIRE(machine.ToString() == MachineState(5, "waiting for quarter"));
	}

	SECTION("can change count of gumballs if the crank is turned with a quarter.")
	{
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == MachineState(4, "waiting for quarter"));
	}

	SECTION("is sold out if it has not gumballs.")
	{
		std::stringstream strm;
		with_state::CGumballMachine machine{ 0, strm };

		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == MachineState(0, "sold out"));
	}

	SECTION("is sold out if all the gumballs have been sold.")
	{
		std::stringstream strm;
		with_state::CGumballMachine machine{ 1, strm };

		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == MachineState(0, "sold out"));
	}
}