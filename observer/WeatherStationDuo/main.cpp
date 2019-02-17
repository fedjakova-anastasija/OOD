#include "WeatherData.h"

int main()
{
	CWeatherData in("in");
	CWeatherData out("out");
	CDisplay display;
	out.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	in.RegisterObserver(statsDisplay, 2);

	out.SetMeasurements(3, 0.7, 760);
	in.SetMeasurements(4, 0.8, 761);

	in.SetMeasurements(10, 0.8, 761);
	out.SetMeasurements(-10, 0.8, 761);
	return 0;
}