#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 2);

	wd.SetMeasurements(3, 0.7, 760, 10, 180);
	wd.SetMeasurements(4, 0.8, 761, 20, 360);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 10, 180);
	wd.SetMeasurements(-10, 0.8, 761, 10, 180);
	return 0;
}