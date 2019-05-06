#include "stdafx.h"
#include "CTriangle.h"

using namespace std;

CTriangle::CTriangle(PointD firstPoint, PointD secondPoint, PointD thirdPoint)
	: m_firstPoint(firstPoint)
	, m_secondPoint(secondPoint)
	, m_thirdPoint(thirdPoint)
{
}

RectD CTriangle::GetFrame() const
{
	double minX = min({ m_firstPoint.x, m_secondPoint.x, m_thirdPoint.x });
	double minY = min({ m_firstPoint.y, m_secondPoint.y, m_thirdPoint.y });
	double maxX = max({ m_firstPoint.x, m_secondPoint.x, m_thirdPoint.x });
	double maxY = max({ m_firstPoint.y, m_secondPoint.y, m_thirdPoint.y });

	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CTriangle::SetFrame(const RectD& rect)
{
	RectD oldFrame = GetFrame();
	m_firstPoint.x = rect.left + (m_firstPoint.x - oldFrame.left) / (oldFrame.width / rect.width);
	m_firstPoint.y = rect.top + (m_firstPoint.y - oldFrame.top) / (oldFrame.height / rect.height);

	m_secondPoint.x = rect.left + (m_secondPoint.x - oldFrame.left) / (oldFrame.width / rect.width);
	m_secondPoint.y = rect.top + (m_secondPoint.y - oldFrame.top) / (oldFrame.height / rect.height);

	m_thirdPoint.x = rect.left + (m_thirdPoint.x - oldFrame.left) / (oldFrame.width / rect.width);
	m_thirdPoint.y = rect.top + (m_thirdPoint.y - oldFrame.top) / (oldFrame.height / rect.height);
}

void CTriangle::Draw(ICanvas& canvas)
{
	SetCanvasStyles(canvas);
	canvas.MoveTo(m_firstPoint.x, m_firstPoint.y);
	canvas.LineTo(m_secondPoint.x, m_secondPoint.y);
	canvas.LineTo(m_thirdPoint.x, m_thirdPoint.y);
	canvas.LineTo(m_firstPoint.x, m_firstPoint.y);
}
