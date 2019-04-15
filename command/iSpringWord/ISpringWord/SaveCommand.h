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
	void Html() const;

	std::string m_title;
	std::vector<CConstDocumentItem> m_items;

	void CheckEscapes(std::string& text) const;
};
