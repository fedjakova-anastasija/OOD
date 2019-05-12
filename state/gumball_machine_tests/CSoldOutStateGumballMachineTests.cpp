#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

namespace CSoldOutStateTests
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
} // namespace CSoldOutStateTests

TEST_CASE("when gumball machine with state has sold out state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	CSoldOutStateTests::CGumballMachine machine(1, out);
	with_state::CSoldOutState soldStateMachine(machine, out);

	SECTION("can not insert quarter")
	{
		soldStateMachine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("can not eject a quarter")
	{
		soldStateMachine.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
	}

	SECTION("can not turn a crank")
	{
		soldStateMachine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no gumballs\n");
	}

	SECTION("can not dispense")
	{
		soldStateMachine.Dispense();
		REQUIRE(out.str() == "No gumball dispensed\n");
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = soldStateMachine.ToString();
		REQUIRE(str == "sold out");
	}
}