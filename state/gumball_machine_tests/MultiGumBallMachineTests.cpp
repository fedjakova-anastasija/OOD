#include "../gumball_machine/MultiGumBallMachine.h"
#include "pch.h"

TEST_CASE("Сan set the correct initial state of multi machine.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}
TEST_CASE("Сan change count of quarters after inserting additional quarters.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 2
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	machine.InsertQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}
TEST_CASE("Сan eject the quarters.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };
	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 2
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	machine.InsertQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
	strm.str("");
	output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	machine.EjectQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can eject the quarters if gumball machine is sold out.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 1 };
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Quarters: 1
Machine is sold out
)";
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
	strm.str("");
	output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Quarters: 0
Machine is sold out
)";
	machine.EjectQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can change count of gumballs if you turn crank.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 4 gumballs
Quarters: 1
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can insert only 5 additional quarters.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 5
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
	strm.str("");
	output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 5
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can insert additional gumballs in initial state machine.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 0 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	machine.Addition(5);
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can add 0 gumballs.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	machine.Addition(0);
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can add gumballs after inserting the quarters.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 6 gumballs
Quarters: 1
Machine is waiting for turn of crank
)";
	machine.InsertQuarter();
	machine.Addition(1);
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can add gumballs after ejecting the quarters.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 6 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	machine.InsertQuarter();
	machine.EjectQuarter();
	machine.Addition(1);
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can add gumballs after turning the crank.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 5 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.Addition(1);
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}

TEST_CASE("Can add gumballs then the gumball machine is empty.")
{
	std::stringstream strm;
	with_multi_state::CGumballMachine machine{ 0 };

	std::string output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Quarters: 0
Machine is sold out
)";
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
	strm.str("");
	output = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 5 gumballs
Quarters: 0
Machine is waiting for quarter
)";
	machine.Addition(5);
	strm << machine.ToString();
	REQUIRE(strm.str() == output);
}