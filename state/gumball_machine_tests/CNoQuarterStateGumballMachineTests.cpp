#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

namespace CNoQuarterStateTests
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
} // namespace CHasQuarterStateTests

TEST_CASE("when gumball machine with state has no quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	CNoQuarterStateTests::CGumballMachine machine(1, out);
	with_state::CNoQuarterState noQuarterStateMachine(machine, out);

	SECTION("can insert quarter")
	{
		noQuarterStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
	}
	
	SECTION("can not eject a quarter")
	{
		noQuarterStateMachine.EjectQuarter();
		REQUIRE(out.str() == "You haven't inserted a quarter\n");
	}

	SECTION("can turn a crank")
	{
		noQuarterStateMachine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no quarter\n");
	}

	SECTION("can not dispense")
	{
		noQuarterStateMachine.Dispense();
		REQUIRE(out.str() == "You need to pay first\n");
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = noQuarterStateMachine.ToString();
		REQUIRE(str == "waiting for quarter");
	}
}