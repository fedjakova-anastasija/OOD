#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

namespace CSoldStateTests
{
class CGumballMachine : public with_state::IGumballMachine
{
public:
	CGumballMachine(unsigned count, std::stringstream& output)
		: m_count(count)
		, m_out(output){};

	unsigned GetBallCount() const override
	{
		return m_count;
	};

private:
	void InsertAdditionalQuarter()
	{
		if (m_quartersCount < MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
		}
	}

	void ReleaseBall() override{};

	void SetSoldOutState() override{};
	void SetNoQuarterState() override{};
	void SetSoldState() override{};
	void SetHasQuarterState() override{};

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_count = 0;
	unsigned m_quartersCount = 0;
	with_state::IState* m_state;
	std::stringstream& m_out;
};
} // namespace CSoldStateTests

TEST_CASE("when gumball machine with state has sold state, it ", "[CSoldStateGumBallMachineTests]")
{
	std::stringstream out;
	CSoldStateTests::CGumballMachine machine(1, out);
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
		CSoldStateTests::CGumballMachine machine(0, out);
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