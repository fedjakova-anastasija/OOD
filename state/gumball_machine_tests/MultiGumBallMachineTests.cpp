#include "../gumball_machine/MultiGumBallMachine.h"
#include "pch.h"

std::string MachineState(unsigned count, unsigned quarters, std::string state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quarters: %3%
Machine is %4%
)");
	return (fmt % count % (count != 1 ? "s" : "") % quarters % state).str();
}

TEST_CASE("Multi gumball machine ")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5, strm };

	SECTION("can set the correct initial state.")
	{
		REQUIRE(machine.ToString() == MachineState(5, 0, "waiting for quarter"));
	}

	SECTION("can change count of quarters after inserting additional quarters.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == MachineState(5, 2, "waiting for turn of crank"));
	}

	SECTION("can eject the quarters.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == MachineState(5, 2, "waiting for turn of crank"));
		strm.str("");
		machine.EjectQuarter();
		REQUIRE(machine.ToString() == MachineState(5, 0, "waiting for quarter"));
	}

	SECTION("can eject the quarters if gumball machine is sold out.")
	{
		std::stringstream strm;
		with_multi_state::CGumballMachine machine{ 1, strm };

		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == MachineState(0, 1, "sold out"));
		strm.str("");
		machine.EjectQuarter();
		REQUIRE(machine.ToString() == MachineState(0, 0, "sold out"));
	}

	SECTION("can change count of gumballs if you turn crank.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == MachineState(4, 1, "waiting for turn of crank"));
	}

	SECTION("can insert only 5 additional quarters.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == MachineState(5, 5, "waiting for turn of crank"));
		strm.str("");
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == MachineState(5, 5, "waiting for turn of crank"));
	}

	SECTION("can insert additional gumballs in initial state machine.")
	{
		std::stringstream strm;
		with_multi_state::CGumballMachine machine{ 0, strm };
		
		machine.Addition(5);
		REQUIRE(machine.ToString() == MachineState(5, 0, "waiting for quarter"));
	}

	SECTION("can add 0 gumballs.")
	{
		machine.Addition(0);
		REQUIRE(machine.ToString() == MachineState(5, 0, "waiting for quarter"));
	}

	SECTION("can add gumballs after inserting the quarters.")
	{
		machine.InsertQuarter();
		machine.Addition(1);
		REQUIRE(machine.ToString() == MachineState(6, 1, "waiting for turn of crank"));
	}

	SECTION("can add gumballs after ejecting the quarters.")
	{
		machine.InsertQuarter();
		machine.EjectQuarter();
		machine.Addition(1);
		REQUIRE(machine.ToString() == MachineState(6, 0, "waiting for quarter"));
	}

	SECTION("can add gumballs after turning the crank.")
	{
		machine.InsertQuarter();
		machine.TurnCrank();
		machine.Addition(1);
		REQUIRE(machine.ToString() == MachineState(5, 0, "waiting for quarter"));
	}

	SECTION("can add gumballs when the gumball machine is empty.")
	{
		std::stringstream strm;
		with_multi_state::CGumballMachine machine{ 0, strm };
		
		REQUIRE(machine.ToString() == MachineState(0, 0, "sold out"));
		strm.str("");
		machine.Addition(5);
		REQUIRE(machine.ToString() == MachineState(5, 0, "waiting for quarter"));
	}
}