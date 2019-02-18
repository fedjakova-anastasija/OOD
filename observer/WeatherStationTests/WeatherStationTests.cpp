#include "../WeatherStation/Observer.h"
#include "../WeatherStation/WeatherData.h"
#include "pch.h"

class CDisplayTest: public IObserver<SWeatherInfo>
{
public:
	CDisplayTest(CObservable<SWeatherInfo>& observable, std::stringstream& strm, int priority)
		: m_observable(observable)
		, m_strm(strm)
	    , m_priority(priority)
	{
		m_observable.RegisterObserver(*this, m_priority);
	}

private:
	void Update(const SWeatherInfo& data) override
	{
		m_strm << m_priority;
		m_strm << " remove/";
		m_observable.RemoveObserver(*this);
	}

	CObservable<SWeatherInfo>& m_observable;
	std::stringstream& m_strm;
	int m_priority = 0;
};

TEST_CASE("Check secure notification")
{
	CWeatherData wd;
	std::stringstream strm;

	CDisplayTest firstDisplay(wd, strm, 1);
	CDisplayTest secondDisplay(wd, strm, 2);
	wd.RegisterObserver(firstDisplay, 1);
	wd.RegisterObserver(secondDisplay, 2);
	wd.SetMeasurements(3, 0.7, 760);
	REQUIRE(strm.str() == "1 remove/2 remove/");
	strm.clear();
	wd.SetMeasurements(4, 0.8, 761);
	REQUIRE(strm.str() == "1 remove/2 remove/");
}

TEST_CASE("Check observers priority")
{
	CWeatherData wd;
	std::stringstream strm;
	CDisplayTest firstDisplay(wd, strm, 1);
	CDisplayTest secondDisplay(wd, strm, 2);

	wd.RegisterObserver(secondDisplay, 2);
	wd.RegisterObserver(firstDisplay, 1);

	wd.NotifyObservers();

	REQUIRE(strm.str() == "1 remove/2 remove/");
}