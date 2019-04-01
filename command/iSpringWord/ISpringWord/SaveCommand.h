#pragma once

#include "IDocument.h"

class SaveCommand
{
public:
	SaveCommand(const boost::filesystem::path&);
	void Save() const;

	void SetTitle(const std::string&);
	void AddItem(const CConstDocumentItem&);

private:
	boost::filesystem::path m_path;

	void SetPath(const boost::filesystem::path& path);
	void CopyImages() const;

	void OutputHead(std::ofstream& out) const;
	void OutputBody(std::ofstream& out) const;
	void OutputHtml() const;

	std::string m_title;
	std::vector<CConstDocumentItem> m_items;

	const std::vector<std::pair<std::string, std::string>> ESCAPES = {
		{ "&", "&amp;" },
		{ "\"", "&quot;" },
		{ "\'", "&apos;" },
		{ "<", "&lt;" },
		{ ">", "&gt;" },
	};

	void ProccessEscapes(std::string& text) const;
};
