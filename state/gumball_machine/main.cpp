#include "GumBallMachineWithDynamicallyCreatedState.h"
#include "GumBallMachineWithState.h"
#include "Menu.h"
#include "MultiGumBallMachine.h"
#include "MultiNaiveGumBallMachine.h"
#include "NaiveGumBallMachine.h"
#include <sstream>

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType& m, stringstream& output)
{
	cout << m.ToString() << endl;

	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();

	cout << m.ToString() << endl;

	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.EjectQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();

	cout << m.ToString() << endl;

	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();
	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();
	output.str("");
	m.EjectQuarter();
	cout << output.str();

	cout << m.ToString() << endl;

	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();
	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();
	output.str("");
	m.InsertQuarter();
	cout << output.str();
	output.str("");
	m.TurnCrank();
	cout << output.str();

	cout << m.ToString() << endl;
}

//void TestNaiveGumballMachine()
//{
//	naive::CGumballMachine m(5);
//	TestGumballMachine(m);
//}

void TestGumballMachineWithState()
{
	stringstream output;
	output.str("");
	with_state::CGumballMachine m(5, output);
	TestGumballMachine(m, output);
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
	stringstream output;
	output.str("");
	naive_multi::CGumballMachine m(5, output);
	TestGumballMachine(m, output);
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

	stringstream output;
	CMenu menu(output);
	menu.Run();

	return 0;	
}