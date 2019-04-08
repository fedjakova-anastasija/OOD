#include "../ISpringWord/stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(int& width, int const& newWidth, int& height, int const& newHeight)
	: m_height(height)
	, m_width(width)
	, m_newHeight(newHeight)
	, m_newWidth(newWidth)
{
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_height, m_newHeight);
	std::swap(m_width, m_newWidth);
}

void CResizeImageCommand::DoUnexecute()
{
	std::swap(m_width, m_newWidth);
	std::swap(m_height, m_newHeight);
}
