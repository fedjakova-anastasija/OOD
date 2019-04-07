#include "stdafx.h"
#include "Image.h"
#include "ResizeImageCommand.h"

CImage::CImage(const boost::filesystem::path& path, int width, int height, ICommandHistory& history)
	: m_path(path)
	, m_height(height)
	, m_width(width)
	, m_history(history)
{
}

boost::filesystem::path CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_history.AddAndExecuteCommand(std::make_unique<CResizeImageCommand>(m_width, width, m_height, height));
}
