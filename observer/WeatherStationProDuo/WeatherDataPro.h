#pragma once
#include "Info.h"
#include "Observer.h"
#include "WindInfo.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct SWeatherInfoPro
{
	double windSpeed = 0;
	double windDirection = 0;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string indicatorType;
};

class CDisplayPro : public IObserver<SWeatherInfoPro>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfoPro const& data) override
	{
		std::cout << "Indicator type: " << data.indicatorType << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplayPro : public IObserver<SWeatherInfoPro>
{
private:
	CInfo windSpeed;
	CWindInfo windDirection;
	CInfo temperature;
	CInfo humidity;
	CInfo pressure;

	void Update(SWeatherInfoPro const& data) override
	{
		std::cout << "Indicator type: " << data.indicatorType << std::endl;
		std::cout << "Wind speed info: " << std::endl;
		windSpeed.UpdateInfo(data.windSpeed);
		std::cout << "Wind direction info: " << std::endl;
		windDirection.UpdateInfo(data.windDirection);
		std::cout << "Temperature info: " << std::endl;
		temperature.UpdateInfo(data.temperature);
		std::cout << "Humidify info:" << std::endl;
		humidity.UpdateInfo(data.humidity);
		std::cout << "Pressure info:" << std::endl;
		pressure.UpdateInfo(data.pressure);
	}
};

class CWeatherDataPro : public CObservable<SWeatherInfoPro>
{
public:
	CWeatherDataPro(std::string const& indicatorType)
		: m_indicatorType(indicatorType)
	{
	}
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
	SWeatherInfoPro GetChangedData() const override
	{
		SWeatherInfoPro info;
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.indicatorType = m_indicatorType;
		return info;
	}

private:
	double m_windSpeed = 0;
	double m_windDirection = 0;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::string m_indicatorType;
};
