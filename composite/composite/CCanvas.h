#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream& ostream, double height, double width);

	virtual void SetLineColor(RGBAColor color) override;
	virtual void MoveTo(double x, double y) override;
	virtual void LineTo(double x, double y) override;
	virtual void DrawEllipse(double left, double top, double width, double height) override;

	virtual void BeginFill(RGBAColor color) override;
	virtual void EndFill() override;

	~CCanvas();

private:
	void OpenPath();
	void ClosePath();

	int m_lineWidth = 1;
	double m_height;
	double m_width;
	RGBAColor m_lineColor = 0;
	RGBAColor m_fillColor = NULL;
	std::ostream& m_output;
	bool m_pathOpened = false;
};
