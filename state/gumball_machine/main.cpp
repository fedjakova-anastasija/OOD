#include "GumBallMachineWithDynamicallyCreatedState.h"
#include "GumBallMachineWithState.h"
#include "Menu.h"
#include "MultiGumBallMachine.h"
#include "MultiNaiveGumBallMachine.h"
#include "NaiveGumBallMachine.h"
#include <iostream>

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType& m)
{
	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();

	m.InsertQuarter();
	m.EjectQuarter();
	m.TurnCrank();

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();

	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;
}

//void TestNaiveGumballMachine()
//{
//	naive::CGumballMachine m(5);
//	TestGumballMachine(m);
//}

void TestGumballMachineWithState()
{
	with_state::CGumballMachine m(5, cout);
	TestGumballMachine(m);
}
//
//void TestGumballMachineWithDynamicState()
//{
//	with_dynamic_state::CGumballMachine m(5);
//	TestGumballMachine(m);
//}
//
//void TestMultiGumballMachine()
//{
//	with_multi_state::CGumballMachine m(5);
//	TestGumballMachine(m);
//}
//
void TestMultiNaiveGumballMachine()
{	
	naive_multi::CGumballMachine m(5, cout);
	TestGumballMachine(m);
}

int main()
{
	/*cout << "\n-----------------\n";
	TestGumballMachineWithState();
	
	cout << "\n-----------------\n";
	TestMultiNaiveGumballMachine();*/

	/*TestNaiveGumballMachine();

	cout << "\n-----------------\n";
	TestGumballMachineWithDynamicState();

	cout << "\n-----------------\n";
	TestMultiGumballMachine();*/

	CMenu menu;
	menu.Run();

	return 0;	
}