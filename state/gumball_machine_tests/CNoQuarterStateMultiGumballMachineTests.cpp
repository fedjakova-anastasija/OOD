#include "../gumball_machine/MultiGumBallMachine.h"
#include "pch.h"

namespace CNoQuarterStateTests
{
class CGumballMachine : public with_multi_state::IGumballMachine
{
public:
	CGumballMachine(unsigned count, std::stringstream& output)
		: m_count(count)
		, m_out(output){};

	void InsertAdditionalQuarter() override
	{
		if (m_quartersCount != MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
		}
	};
	void Addition(unsigned count) override
	{
		m_count += count;
	};

	unsigned GetBallCount() const override
	{
		return m_count;
	};

	unsigned GetQuartersCount() const override
	{
		return m_quartersCount;
	};

private:
	void EjectAdditionalQuarter() override
	{
		m_quartersCount = 0;
	}

	void AddGumballs(unsigned gumballsCount) override
	{
		m_count += gumballsCount;
	}

	void ReleaseBall() override{};

	void ProcessQuarter() override
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}

	void SetSoldOutState() override{};
	void SetNoQuarterState() override{};
	void SetSoldState() override{};
	void SetHasQuarterState() override{};

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_count = 0;
	unsigned m_quartersCount = 0;
	with_multi_state::IState* m_state;
	std::stringstream& m_out;
};
} // namespace CHasQuarterStateTests

TEST_CASE("when multi gumball machine has no quarter state, it ", "[CSoldOutStateTests]")
{
	std::stringstream out;
	CNoQuarterStateTests::CGumballMachine machine(1, out);
	with_multi_state::CNoQuarterState noQuarterStateMachine(machine, out);

	SECTION("can insert quarter")
	{
		noQuarterStateMachine.InsertQuarter();
		REQUIRE(out.str() == "");
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

	SECTION("can add gumballs")
	{
		REQUIRE(machine.GetBallCount() == 1);
		noQuarterStateMachine.Addition(1);
		REQUIRE(machine.GetBallCount() == 2);
	}

	SECTION("shows delivering a gumball message")
	{
		auto str = noQuarterStateMachine.ToString();
		REQUIRE(str == "waiting for quarter");
	}
}