#pragma once
#include "Info.h"
#include "Observer.h"
#include "WindInfo.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct SWeatherInfo
{
	double windSpeed = 0;
	double windDirection = 0;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
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
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	CInfo windSpeed;
	CWindInfo windDirection;
	CInfo temperature;
	CInfo humidity;
	CInfo pressure;

	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Wind speed info: " << std::endl;
		windSpeed.UpdateInfo(data.windSpeed);
		std::cout << "Wind direction info: " << std::endl;
		windDirection.UpdateInfo(data.windDirection);
		std::cout << "Temperature info: " << std::endl;
		temperature.UpdateInfo(data.temperature);
		std::cout << "Humidity info:" << std::endl;
		humidity.UpdateInfo(data.humidity);
		std::cout << "Pressure info:" << std::endl;
		pressure.UpdateInfo(data.pressure);
	}
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	double GetWindDirection() const
	{
		return m_windDirection;
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

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_windSpeed = 0;
	double m_windDirection = 0;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
