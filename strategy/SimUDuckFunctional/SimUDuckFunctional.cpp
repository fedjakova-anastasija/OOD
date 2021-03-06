#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

using FlyBehavior = std::function<void()>;
using QuackBehavior = std::function<void()>;
using DanceBehavior = std::function<void()>;

FlyBehavior FlyWithWings()
{
	return [flightsCount = 0]() mutable {
		cout << "I'm flying with wings!!" << endl;
		cout << "Flights count:" << ++flightsCount << endl;
	};
}

void FlyNoWay(){}

void WaltzDanceBehavior()
{
	cout << "I'm dancing waltz!!!" << endl;
}

void MinuetDanceBehavior()
{
	cout << "I'm dancing minuet!!!" << endl;
}

void DanceNoWay(){}

void QuackQuackBehavior()
{
	cout << "Quack Quack!!!" << endl;
}

void SqueakBehavior()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuackBehavior(){}

class Duck
{
public:
	Duck(FlyBehavior flyBehavior,
		QuackBehavior quackBehavior,
		DanceBehavior danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehavior flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackQuackBehavior, WaltzDanceBehavior)
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
		: Duck(FlyWithWings(), QuackQuackBehavior, MinuetDanceBehavior)
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
		: Duck(FlyNoWay, QuackQuackBehavior, DanceNoWay)
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