#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream& ostream, double height, double width);

	void SetThickness(float thickness) override;

	virtual void SetLineColor(RGBAColor color) override;
	virtual void MoveTo(double x, double y) override;
	virtual void LineTo(double x, double y) override;
	virtual void DrawEllipse(double left, double top, double width, double height) override;

	virtual void BeginFill(RGBAColor color) override;
	virtual void EndFill() override;

	~CCanvas();

private:
	void Begin();
	void End();

	double m_height;
	double m_width;
	float m_outlineThickness = 1;
	RGBAColor m_lineColor = 0;
	RGBAColor m_fillColor = 0;
	std::ostream& m_output;
	bool m_pathOpened = false;
};
