#pragma once
#include <climits>
using namespace std;

class CInfo
{
public:
	void UpdateInfo(double indicator)
	{
		if (indicator < m_minValue)
		{
			m_minValue = indicator;
		}

		if (m_maxValue < indicator)
		{
			m_maxValue = indicator;
		}

		m_accValue += indicator;
		++m_counterValue;

		std::cout << "Max value " << m_maxValue << std::endl;
		std::cout << "Min value " << m_minValue << std::endl;
		std::cout << "Average value " << m_accValue / m_counterValue << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0.0;
	size_t m_counterValue = 0;
};