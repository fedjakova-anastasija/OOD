#include "stdafx.h"
#include "CCanvas.h"

using namespace std;

CCanvas::CCanvas(std::ostream& ostream, double height, double width)
	: m_output(ostream)
	, m_height(height)
	, m_width(width)
{
	m_output << "<svg version = \"1.1\" encoding=\"UTF - 8\" xmlns = \"http://www.w3.org/2000/svg\""
			 << " height=\"" << m_height << "\""
			 << " width=\"" << m_width << "\">" << endl;
}

CCanvas::~CCanvas()
{
	if (m_pathOpened)
	{
		CCanvas::ClosePath();
	}

	m_output << "</svg>";
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = color;
	ClosePath();
}

void CCanvas::BeginFill(RGBAColor color)
{
	m_fillColor = color;
}

void CCanvas::EndFill()
{
	m_fillColor = NULL;
}

void CCanvas::MoveTo(double x, double y)
{
	if (!m_pathOpened)
	{
		OpenPath();
	}

	m_output << "M " << x << "," << y << " ";
}

void CCanvas::LineTo(double x, double y)
{
	if (!m_pathOpened)
	{
		MoveTo(0, 0);
	}

	m_output << "L " << x << "," << y << " ";
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	if (m_pathOpened)
	{
		ClosePath();
	}

	m_output << " <ellipse";
	m_output << " stroke=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_lineColor << "\" stroke-width=\"" << m_lineWidth << "\"";
	if (m_fillColor)
	{
		m_output << " fill=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_fillColor << "\"";
	}
	else
	{
		m_output << " fill=\"none\"";
	}
	m_output << " cx=\"" << left << "\" cy=\"" << top << "\" rx=\"" << width << "\" ry=\"" << height << "\" />" << endl;
	ClosePath();
}

void CCanvas::OpenPath()
{
	m_pathOpened = true;
	m_output << "<path";
	m_output << " stroke=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_lineColor << "\" stroke-width=\"" << m_lineWidth << "\"";
	if (m_fillColor)
	{
		m_output << " fill=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_fillColor << "\"";
	}
	else
	{
		m_output << " fill=\"none\"";
	}
	m_output << " d=\"";
}

void CCanvas::ClosePath()
{
	if (m_pathOpened)
	{
		m_output << "\" />" << endl;
		m_pathOpened = false;
		EndFill();
	}
}