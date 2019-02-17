#pragma once
#include <climits>

using namespace std;

class CInfo
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

		m_accIndicator += indicator;
		++m_countAcc;

		std::cout << "Max indicator " << m_maxIndicator << std::endl;
		std::cout << "Min indicator " << m_minIndicator << std::endl;
		std::cout << "Average indicator " << m_accIndicator / m_countAcc << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_minIndicator = std::numeric_limits<double>::infinity();
	double m_maxIndicator = -std::numeric_limits<double>::infinity();
	double m_accIndicator = 0;
	unsigned m_countAcc = 0;
};