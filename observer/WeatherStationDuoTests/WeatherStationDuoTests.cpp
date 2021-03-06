#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"
#include "pch.h"

using namespace std;

class CStatsDisplayTest : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplayTest(std::stringstream& strm, const CWeatherData& in, const CWeatherData& out)
		: m_strm(strm)
		, m_in(in)
		, m_out(out)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		m_strm << "Indicator type: ";
		if (&observable == &m_in)
		{
			m_strm << "in/";
		}
		if (&observable == &m_out)
		{
			m_strm << "out/";
		}
	}

	const CWeatherData& m_in;
	const CWeatherData& m_out;
	std::stringstream& m_strm;
};

TEST_CASE("The observer knows from which subject the notification is received")
{
	CWeatherData wdIn("in");
	CWeatherData wdOut("out");
	stringstream strm;
	CStatsDisplayTest display(strm, wdIn, wdOut);

	wdIn.RegisterObserver(display, 1);
	wdIn.NotifyObservers();
	wdOut.RegisterObserver(display, 2);
	wdOut.NotifyObservers();

	REQUIRE(strm.str() == "Indicator type: in/Indicator type: out/");
}