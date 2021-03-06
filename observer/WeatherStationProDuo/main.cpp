#include "WeatherData.h"
#include "WeatherDataPro.h"

int main()
{
	CWeatherData in("in");
	CWeatherDataPro out("out");
	CDisplayPro display;
	out.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	in.RegisterObserver(statsDisplay, 2);

	out.SetMeasurements(3, 0.7, 760, 10, 180);
	in.SetMeasurements(4, 0.8, 761);

	in.SetMeasurements(10, 0.8, 761);
	out.SetMeasurements(-10, 0.8, 761, 0, 0);
	return 0;
}