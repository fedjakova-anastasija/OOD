#pragma once
#include "Info.h"
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string indicatorType;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Indicator type: " << data.indicatorType << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Indicator type: " << data.indicatorType << std::endl;
		std::cout << "Temperature info: " << std::endl;
		temperature.UpdateInfo(data.temperature);
		std::cout << "Humidity info:" << std::endl;
		humidity.UpdateInfo(data.humidity);
		std::cout << "Pressure info:" << std::endl;
		pressure.UpdateInfo(data.pressure);
	}

	CInfo temperature;
	CInfo humidity;
	CInfo pressure;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string const& indicatorType)
		: m_indicatorType(indicatorType)
	{
	}
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.indicatorType = m_indicatorType;
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::string m_indicatorType;
};
