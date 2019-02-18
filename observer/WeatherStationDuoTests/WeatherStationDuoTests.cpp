#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"
#include "pch.h"

using namespace std;

class CStatsDisplayTest : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplayTest(std::ostream& output)
		: m_output(output)
	{
	}

private:
	ostream& m_output;
	void Update(SWeatherInfo const& data) override
	{
		m_output << "Indicator type: " << data.indicatorType << "/ ";
	}
};

class CWeatherDataTest : public CObservable<SWeatherInfo>
{
public:
	CWeatherDataTest(std::string const& indicatorType)
		: m_indicatorType(indicatorType)
	{
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.indicatorType = m_indicatorType;
		return info;
	}

private:
	std::string m_indicatorType;
};

TEST_CASE("Check observations of multiple subjects")
{
	ostringstream output;
	CStatsDisplayTest display(output);
	CWeatherDataTest wdIn("in");
	CWeatherDataTest wdOut("out");

	wdIn.RegisterObserver(display, 1);
	wdOut.RegisterObserver(display, 2);
	wdIn.NotifyObservers();
	wdOut.NotifyObservers();

	REQUIRE(output.str() == "Indicator type: in/ Indicator type: out/ ");
	output = ostringstream();
}