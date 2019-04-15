#include "../ISpringWord/stdafx.h"
#include "AddImageCommand.h"
#include "Image.h"

CAddImageCommand::CAddImageCommand(ICommandHistory& history, std::vector<CDocumentItem>& items, const boost::filesystem::path& path, int width, int height, const std::string& dirName, boost::optional<size_t> pos)
	: m_items(items)
	, m_pos(pos)
{
	SetImage(history, path, width, height, dirName);
}

CAddImageCommand::~CAddImageCommand()
{
	if (!m_executed)
	{
		boost::system::error_code errorCode;
		boost::filesystem::remove(m_image->GetPath(), errorCode);
		std::cout << "CAddImageCommand" << std::endl;
	}
}

void CAddImageCommand::CheckPos()
{
	if (m_pos > m_items.size())
	{
		throw std::invalid_argument("Wrong position!");
	}
}

void CAddImageCommand::DoExecute()
{
	CheckPos();
	if (m_pos != boost::none)
	{
		m_items.emplace(m_items.begin() + m_pos.get(), CDocumentItem(m_image, nullptr));
	}
	else
	{
		m_items.emplace_back(CDocumentItem(m_image, nullptr));
	}
}

void CAddImageCommand::DoUnexecute()
{
	if (m_pos != boost::none)
	{
		m_items.erase(m_items.begin() + m_pos.get());
	}
	else
	{
		m_items.pop_back();
	}
}

void CAddImageCommand::SetImage(ICommandHistory& history, const boost::filesystem::path& path, int width, int height, const std::string& dirName)
{
	boost::filesystem::path imagesDir = CreateNewDir(dirName);
	
	std::string extension = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extension);
	CheckExtension(extension);
	std::string fileName = boost::filesystem::unique_path().string() + extension;

	boost::filesystem::path newPath = imagesDir.stem();
	newPath = imagesDir.string() + "/" + fileName;
	boost::filesystem::copy_file(path, (imagesDir.string() + "/" + fileName));

	m_image = std::make_shared<CImage>(newPath, width, height, history);
}

boost::filesystem::path CAddImageCommand::CreateNewDir(const std::string& dirName)
{
	boost::filesystem::path imagesDir = boost::filesystem::path(dirName);
	boost::filesystem::create_directory(imagesDir);
	return imagesDir;
}

void CAddImageCommand::CheckExtension(std::string extension)
{
	if (extension != ".jpg" && extension != ".png" && extension != ".gif")
	{
		throw std::logic_error("Wrong file extension!");
	}
}