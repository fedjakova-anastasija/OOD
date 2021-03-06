#include "stdafx.h"
#include "CCanvas.h"

using namespace std;

CCanvas::CCanvas(std::ostream& ostream, double height, double width)
	: m_output(ostream)
	, m_height(height)
	, m_width(width)
{
	m_output << "<svg version = \"1.1\" encoding=\"UTF-8\" xmlns = \"http://www.w3.org/2000/svg\""
			 << " height=\"" << m_height << "\""
			 << " width=\"" << m_width << "\">" << endl;
}

CCanvas::~CCanvas()
{
	if (m_pathOpened)
	{
		CCanvas::End();
	}

	m_output << "</svg>";
}

void CCanvas::SetThickness(float thickness)
{
	m_outlineThickness = thickness;
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = color;
	End();
}

void CCanvas::BeginFill(RGBAColor color)
{
	m_fillColor = color;
}

void CCanvas::EndFill()
{
	m_fillColor = 0;
}

void CCanvas::MoveTo(double x, double y)
{
	if (!m_pathOpened)
	{
		Begin();
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
		End();
	}

	m_output << " <ellipse";
	m_output << " stroke=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_lineColor << "\" stroke-width=\"" << m_outlineThickness << "\"";
	if (m_fillColor)
	{
		m_output << " fill=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_fillColor << "\"";
	}
	else
	{
		m_output << " fill=\"none\"";
	}
	m_output << " cx=\"" << left << "\" cy=\"" << top << "\" rx=\"" << width << "\" ry=\"" << height << "\" />" << endl;
	End();
}

void CCanvas::Begin()
{
	m_pathOpened = true;
	m_output << "<path";
	m_output << " stroke=\"#" << std::setfill('0') << std::setw(6) << std::hex << m_lineColor << "\" stroke-width=\"" << m_outlineThickness << "\"";
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

void CCanvas::End()
{
	if (m_pathOpened)
	{
		m_output << "\" />" << endl;
		m_pathOpened = false;
		EndFill();
	}
}