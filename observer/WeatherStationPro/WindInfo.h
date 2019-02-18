#pragma once
#include <climits>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class CWindInfo
{
public:
	void UpdateInfo(double indicator)
	{
		if (indicator < m_minIndicator)
		{
			m_minIndicator = indicator;
		}

		if (m_maxIndicator < indicator)
		{
			m_maxIndicator = indicator;
		}

		m_x += cos(indicator * M_PI / 180);
		m_y += sin(indicator * M_PI / 180);
		double deg = atan2(m_y, m_x) * 180 / M_PI;

		std::cout << "Max indicator " << m_maxIndicator << std::endl;
		std::cout << "Min indicator " << m_minIndicator << std::endl;
		std::cout << "Average indicator " << ((deg >= 0) ? deg : deg + 360) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_x = 0;
	double m_y = 0;
	double m_minIndicator = std::numeric_limits<double>::infinity();
	double m_maxIndicator = -std::numeric_limits<double>::infinity();
};