#include "stdafx.h"
#include "Image.h"
#include "ResizeImageCommand.h"

CImage::CImage(const boost::filesystem::path& path, int width, int height, ICommandHistory& history)
	: m_path(path)
	, m_height(height)
	, m_width(width)
	, m_history(history)
{
	CheckPath(path);
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

void CImage::CheckPath(const boost::filesystem::path& path)
{
	if (boost::filesystem::is_regular_file(path))
	{
		std::string extensionFile = boost::filesystem::extension(path);
		boost::algorithm::to_lower(extensionFile);

		if (extensionFile != ".jpg" && extensionFile != ".png" && extensionFile != ".gif")
		{
			throw std::logic_error("File extension is incorrect");
		}
	}
	else
	{
		throw std::logic_error("Wrong file name!");
	}
	m_path = path;
}
