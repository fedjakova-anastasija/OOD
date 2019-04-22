#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

TEST_CASE("Сan set the correct initial state.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Machine is waiting for quarter
)";
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("The state of machine cannot change if the crank is turned without a quarter.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Machine is waiting for quarter
)";
	machine.TurnCrank();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can change the state of machine if you insert a quarter.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("The state of machine cannot change if you insert and then eject the quarter.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Machine is waiting for quarter
)";
	machine.InsertQuarter();
	machine.EjectQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Cannot eject a quarter if you haven't inserted it.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Machine is waiting for quarter
)";
	machine.EjectQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can change count of gumballs if the crank is turned with a quarter.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 4 gumballs
Machine is waiting for quarter
)";
	machine.InsertQuarter();
	machine.TurnCrank();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("The state of machine is sold out if it has not gumballs.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 0 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Machine is sold out
)";
	machine.InsertQuarter();
	machine.TurnCrank();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("The state of machine is sold out if all the gumballs have been sold.")
{
	std::stringstream strm;
	with_state::CGumballMachine machine{ 1 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Machine is sold out
)";
	machine.InsertQuarter();
	machine.TurnCrank();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}