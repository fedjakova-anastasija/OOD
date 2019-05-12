//#include "../gumball_machine/MultiNaiveGumBallMachine.h"
//#include "pch.h"
//
//TEST_CASE("when multi naive gumball machine has sold state, it ", "[CSoldStateTests]")
//{
//	std::stringstream out;
//	naive_multi::CGumballMachine machine(1, out);
//
//	SECTION("can not insert quarter")
//	{
//		machine.InsertQuarter();
//		REQUIRE(out.str() == "Please wait, we're already giving you a gumball\n");
//	}
//
//	SECTION("can not eject a quarter")
//	{
//		machine.EjectQuarter();
//		REQUIRE(out.str() == "Sorry you already turned the crank\n");
//	}
//
//	SECTION("can not turn a crank")
//	{
//		machine.TurnCrank();
//		REQUIRE(out.str() == "Turning twice doesn't get you another gumball\n");
//	}
//
//	/*SECTION("can not dispense")
//	{
//		std::stringstream out;
//		naive_multi::CGumballMachine machine(0, out);
//		machine.Dispense();
//		REQUIRE(out.str() == "Oops, out of gumballs\n");
//	}
//
//	SECTION("can dispense")
//	{
//		machine.Dispense();
//		REQUIRE(out.str() == "");
//	}*/
//
//	SECTION("shows delivering a gumball message")
//	{
//		auto str = machine.ToString();
//		REQUIRE(str == "delivering a gumball");
//	}
//}