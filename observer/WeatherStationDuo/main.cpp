#include "WeatherData.h"

int main()
{
	CWeatherData in("in");
	CWeatherData out("out");
	CDisplay display(in, out);
	//out.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay(in, out);
	in.RegisterObserver(statsDisplay, 1);
	out.RegisterObserver(statsDisplay, 1);
	
	in.SetMeasurements(11, 0.8, 761);
	in.SetMeasurements(10, 0.8, 762);

	out.SetMeasurements(3, 0.7, 760);
	out.SetMeasurements(-10, 0.8, 761);
	return 0;
}