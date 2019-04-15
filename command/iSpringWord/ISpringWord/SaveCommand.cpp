#include "../ISpringWord/stdafx.h"
#include "SaveCommand.h"

namespace
{
const std::vector<std::pair<std::string, std::string>> ESCAPES = {
	{ "&", "&amp;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "\"", "&quot;" },
	{ "'", "&apos;" }
};
} // namespace

SaveCommand::SaveCommand(const boost::filesystem::path& path)
{
	SetPath(path);
}

void SaveCommand::Save() const
{
	CopyImages();
	Html();
}

void SaveCommand::CheckEscapes(std::string& text) const
{
	for (auto& it : ESCAPES)
	{
		boost::algorithm::replace_all(text, it.first, it.second);
	}
}

void SaveCommand::SetTitle(const std::string& title)
{
	m_title = title;
	SaveCommand::CheckEscapes(m_title);
}

void SaveCommand::AddItem(const CConstDocumentItem& item)
{
	m_items.emplace_back(item);
}

void SaveCommand::SetPath(const boost::filesystem::path& path)
{
	std::string fileExtension = boost::filesystem::extension(path);
	boost::algorithm::to_lower(fileExtension);

	if (fileExtension != ".html")
	{
		throw std::logic_error("File extension is incorrect");
	}

	m_path = boost::filesystem::complete(path);
	boost::filesystem::path directory = m_path;
	directory.remove_filename();

	if (!boost::filesystem::exists(directory))
	{
		boost::filesystem::create_directory(directory);
	}
}

void SaveCommand::CopyImages() const
{
	boost::filesystem::path imagesFolderPath = (m_path.parent_path() /= boost::filesystem::path("images"));
	boost::filesystem::create_directory(imagesFolderPath);

	for (size_t i = 0; i < m_items.size(); ++i)

	{
		auto item = m_items.at(i);
		if (auto it = item.GetImage())
		{
			boost::filesystem::path path = it->GetPath();
			boost::filesystem::path newPath = imagesFolderPath;
			newPath /= boost::filesystem::path(path.filename());

			if (!boost::filesystem::exists(newPath))
			{
				boost::filesystem::copy_file(boost::filesystem::complete(path), newPath);
			}
		}
	}
}

void SaveCommand::Html() const
{
	std::ofstream output(m_path.string());

	output << "<html>" << std::endl;
	output << "<head>" << std::endl;
	output << "<title>" << m_title << "</title>" << std::endl;
	output << "</head>" << std::endl;
	output << "<body>" << std::endl;

	for (size_t i = 0; i < m_items.size(); ++i)
	{
		auto item = m_items.at(i);
		if (auto image = item.GetImage())
		{
			boost::filesystem::path path = (boost::filesystem::path("images") /= (image->GetPath()).filename());
			output << "<img src='" << path.generic_string() << "' width='" << image->GetWidth() << "' height='" << image->GetHeight() << "' />" << std::endl;
		}
		else
		{
			auto paragraph = item.GetParagraph();
			std::string text = paragraph->GetText();
			SaveCommand::CheckEscapes(text);
			output << "<p>" << text << "</p>" << std::endl;
		}
	}
	output << "</body>" << std::endl;
	output << "</html>" << std::endl;
}
