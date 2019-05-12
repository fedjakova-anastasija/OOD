#include "../gumball_machine/MultiNaiveGumBallMachine.h"
#include "pch.h"

std::string ToString(unsigned count, unsigned quarters, std::string state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Quarters: %3%
Machine is %4%
)");
	return (fmt % count % (count != 1 ? "s" : "") % quarters % state).str();
}

TEST_CASE("Multi naive machine ")
{
	std::stringstream strm;
	naive_multi::CGumballMachine machine{ 5, strm };

	SECTION("can set the correct initial state.")
	{
		REQUIRE(machine.ToString() == ToString(5, 0, "waiting for quarter"));
	}
	SECTION("can change count of quarters after inserting additional quarters.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == ToString(5, 2, "waiting for turn of crank"));
	}
	SECTION("can eject the quarters.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == ToString(5, 2, "waiting for turn of crank"));
		strm.str("");
		machine.EjectQuarter();
		REQUIRE(machine.ToString() == ToString(5, 0, "waiting for quarter"));
	}

	SECTION("can eject the quarters if gumball naive machine is sold out.")
	{
		std::stringstream strm;
		naive_multi::CGumballMachine machine{ 1, strm };
		
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == ToString(0, 1, "sold out"));
		strm.str("");

		machine.EjectQuarter();
		REQUIRE(machine.ToString() == ToString(0, 0, "sold out"));
	}

	SECTION("can change count of gumballs if you turn crank the multi naive machine.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(machine.ToString() == ToString(4, 1, "waiting for turn of crank"));
	}

	SECTION("can insert only 5 additional quarters.")
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == ToString(5, 5, "waiting for turn of crank"));
		strm.str("");
		machine.InsertQuarter();
		REQUIRE(machine.ToString() == ToString(5, 5, "waiting for turn of crank"));
	}

	SECTION("can insert additional gumballs in initial state.")
	{
		std::stringstream strm;
		naive_multi::CGumballMachine machine{ 0, strm };

		machine.Refill(5);
		REQUIRE(machine.ToString() == ToString(5, 0, "waiting for quarter"));
	}

	SECTION("can add 0 gumballs.")
	{
		machine.Refill(0);
		REQUIRE(machine.ToString() == ToString(5, 0, "waiting for quarter"));
	}

	SECTION("can add gumballs after inserting the quarters.")
	{
		machine.InsertQuarter();
		machine.Refill(1);
		REQUIRE(machine.ToString() == ToString(6, 1, "waiting for turn of crank"));
	}

	SECTION("can add gumballs after ejecting the quarters.")
	{
		machine.InsertQuarter();
		machine.EjectQuarter();
		machine.Refill(1);
		REQUIRE(machine.ToString() == ToString(6, 0, "waiting for quarter"));
	}

	SECTION("can add gumballs after turning the crank.")
	{
		machine.InsertQuarter();
		machine.TurnCrank();
		machine.Refill(1);
		REQUIRE(machine.ToString() == ToString(5, 0, "waiting for quarter"));
	}

	SECTION("can add gumballs when the gumball naive machine is empty.")
	{
		std::stringstream strm;
		naive_multi::CGumballMachine machine{ 0, strm };

		REQUIRE(machine.ToString() == ToString(0, 0, "sold out"));
		strm.str("");
		machine.Refill(5);
		REQUIRE(machine.ToString() == ToString(5, 0, "waiting for quarter"));
	}
}