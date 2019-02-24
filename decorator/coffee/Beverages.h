#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

enum CoffeeSize
{
	Standart,
	Double
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(CoffeeSize coffeeSize = CoffeeSize::Standart, const std::string& description = " Coffee")
		: CBeverage(GetCoffeeDescription(coffeeSize) + description)
		, m_coffeeSize(coffeeSize)
	{
	}

	double GetCost() const override
	{
		return 60;
	}

	std::string GetCoffeeDescription(CoffeeSize coffeeSize)
	{
		std::string size;
		switch (coffeeSize)
		{
		case CoffeeSize::Standart:
			size = "Standart";
			break;
		case CoffeeSize::Double:
			size = "Double";
			break;
		default:
			break;
		}
		return size;
	};

protected:
	CoffeeSize m_coffeeSize;
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeeSize coffeeSize = CoffeeSize::Standart)
		: CCoffee(coffeeSize, " Capuccino")
	{
	}

	double GetCost() const override
	{
		return (m_coffeeSize == CoffeeSize::Standart) ? 80 : 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeSize coffeeSize = CoffeeSize::Standart)
		: CCoffee(coffeeSize, " Latte")
	{
	}

	double GetCost() const override
	{
		return (m_coffeeSize == CoffeeSize::Standart) ? 90 : 130;
	}
};

enum TeaType
{
	Black,
	Green,
	Red,
	White
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType teaType = TeaType::Black)
		: CBeverage(GetTeaDescription(teaType) + " Tea")
	{
	}

	double GetCost() const override
	{
		return 30;
	}

	std::string GetTeaDescription(TeaType teaType)
	{
		std::string type;
		switch (teaType)
		{
		case TeaType::Black:
			type = "Black";
			break;
		case TeaType::Green:
			type = "Green";
			break;
		case TeaType::Red:
			type = "Red";
			break;
		case TeaType::White:
			type = "White";
			break;
		default:
			break;
		}
		return type;
	};
};

enum MilkshakeSize
{
	Small,
	Middle,
	Big
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize milkshakeSize = MilkshakeSize::Small)
		: CBeverage(GetMilkshakeDescription(milkshakeSize) + " Milkshake")
		, m_milkshakeSize(milkshakeSize)
	{
	}

	double GetCost() const override
	{
		int price;
		switch (m_milkshakeSize)
		{
		case MilkshakeSize::Small:
			price = 50;
			break;
		case MilkshakeSize::Middle:
			price = 60;
			break;
		case MilkshakeSize::Big:
			price = 80;
			break;
		default:
			break;
		}
		return price;
	}

	std::string GetMilkshakeDescription(MilkshakeSize milkshakeSize)
	{
		std::string size;
		switch (milkshakeSize)
		{
		case MilkshakeSize::Small:
			size = "Small";
			break;
		case MilkshakeSize::Middle:
			size = "Middle";
			break;
		case MilkshakeSize::Big:
			size = "Big";
			break;
		default:
			break;
		}
		return size;
	};

protected:
	MilkshakeSize m_milkshakeSize;
};
