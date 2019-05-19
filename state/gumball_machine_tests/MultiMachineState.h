#include "../gumball_machine/MultiGumBallMachine.h"
#include "pch.h"

namespace MultiMachineState
{
class CGumballMachine : public with_multi_state::IGumballMachine
{
public:
	CGumballMachine(unsigned count, std::ostream& output)
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
	std::ostream& m_out;
};
} // namespace CHasQuarterStateTests
