#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

using FlyFly = std::function<void()>;
using QuackQuack = std::function<void()>;
using DanceDance = std::function<void()>;

FlyFly FlyWithWings()
{
	return [m_flightsCount = 0]() mutable {
		cout << "I'm flying with wings!!" << endl;
		cout << "Flights count:" << ++m_flightsCount << endl;
	};
}

DanceDance WaltzDanceBehavior = []() {
	cout << "I'm dancing waltz!!!" << endl;
};

DanceDance MinuetDanceBehavior = []() {
	cout << "I'm dancing minuet!!!" << endl;
};

DanceDance DanceNoWay = []() { cout << "I'm" << endl; };

FlyFly FlyNoWay = []() {
	cout << "I'm" << endl;
};

QuackQuack SqueakBehavior = []() {
	cout << "Squeek!!!" << endl;
};
QuackQuack QuackBehavior = []() {
	cout << "Quack Quack!!!" << endl;
};
QuackQuack MuteQuackBehavior = []() { cout << "I'm" << endl; };

class Duck
{
public:
	Duck(const FlyFly& flyBehavior,
		const QuackQuack& quackBehavior,
		const DanceDance& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		/*assert(m_quackBehavior);
		assert(m_danceBehavior);*/
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior;
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior;
	}
	void Dance()
	{
		m_danceBehavior;
	}
	void SetFlyBehavior(const FlyFly& flyBehavior)
	{
		//assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyFly m_flyBehavior;
	QuackQuack m_quackBehavior;
	DanceDance m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackBehavior, WaltzDanceBehavior)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), QuackBehavior, MinuetDanceBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings());
	PlayWithDuck(modelDuck);
}