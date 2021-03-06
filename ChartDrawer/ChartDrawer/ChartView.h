#pragma once
#include "IChartView.h"

class ChartView
	: public CStatic
	, public IChartView
{
public:
	ChartView();
	~ChartView();

	virtual void SetData(const Points2D& data) override;

private:
	void UpdateBounds();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	Points2D m_points;
	Point2D m_leftTop;
	Point2D m_rightBottom;
};
