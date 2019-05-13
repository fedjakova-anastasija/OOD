#include "../gumball_machine/GumBallMachineWithState.h"
#include "pch.h"

namespace MachineState
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