#include "stdafx.h"
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
	}
}

void CAddImageCommand::DoExecute()
{
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
	m_items.erase(m_items.begin() + m_pos.get());
}

void CAddImageCommand::SetImage(ICommandHistory& history, const boost::filesystem::path& path, int width, int height, const std::string& dirName)
{
	//boost::filesystem::path imagesFolderPath = boost::filesystem::path(dirName);
	//boost::filesystem::create_directory(imagesFolderPath);

	boost::filesystem::path imagesDir = CreateNewDir(dirName);

	std::string extensionFile = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extensionFile);
	CheckExtension(extensionFile);
	/*if (extensionFile != ".jpg" && extensionFile != ".png" && extensionFile != ".gif")
	{
		throw std::logic_error("Wrong file extension");
	}*/

	std::string newFileName = boost::filesystem::unique_path().string() + extensionFile;

	boost::filesystem::path newRelativePath = imagesDir.stem();
	newRelativePath /= boost::filesystem::path(newFileName);

	boost::filesystem::copy_file(path, (imagesDir /= boost::filesystem::path(newFileName)));
	m_image = std::make_shared<CImage>(newRelativePath, width, height, history);
}

boost::filesystem::path CAddImageCommand::CreateNewDir(const std::string& dirName)
{
	boost::filesystem::path imagesDir = boost::filesystem::path(dirName);
	boost::filesystem::create_directory(imagesDir);
	return imagesDir;
}

void CAddImageCommand::CheckExtension(std::string extensionFile)
{
		if (extensionFile != ".jpg" && extensionFile != ".png" && extensionFile != ".gif")
	{
		throw std::logic_error("Wrong file extension");
	}
}