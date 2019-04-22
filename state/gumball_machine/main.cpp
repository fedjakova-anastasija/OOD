#include "NaiveGumBallMachine.h"
#include "GumBallMachineWithState.h"
#include "MultiGumBallMachine.h"
#include "MultiNaiveGumBallMachine.h"
#include "GumBallMachineWithDynamicallyCreatedState.h"

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType & m)
{
	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.EjectQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;
}

void TestNaiveGumballMachine()
{
	naive::CGumballMachine m(5);
	TestGumballMachine(m);
}

void TestGumballMachineWithState()
{
	with_state::CGumballMachine m(5);
	TestGumballMachine(m);
}

void TestGumballMachineWithDynamicState()
{
	with_dynamic_state::CGumballMachine m(5);
	TestGumballMachine(m);
}

void TestMultiGumballMachine()
{
	with_multi_state::CGumballMachine m(5);
	TestGumballMachine(m);
}

void TestMultiNaiveGumballMachine()
{
	naive_multi::CGumballMachine m(5);
	TestGumballMachine(m);
}

int main()
{
	TestNaiveGumballMachine();

	cout << "\n-----------------\n";
	TestGumballMachineWithState();

	cout << "\n-----------------\n";
	TestGumballMachineWithDynamicState();

	cout << "\n-----------------\n";
	TestMultiGumballMachine();

	cout << "\n-----------------\n";
	TestMultiNaiveGumballMachine();

	return 0;
}
