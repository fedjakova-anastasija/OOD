#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "ICommandHistory.h"

class CAddImageCommand : public CAbstractCommand
{
public:
	CAddImageCommand(ICommandHistory& history, std::vector<CDocumentItem>& items, const boost::filesystem::path& path, int width, int height, const std::string& dirName, boost::optional<size_t> pos = boost::none);
	~CAddImageCommand() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	void SetImage(ICommandHistory& history, const boost::filesystem::path& path, int width, int height, const std::string& dirName);
	void CheckPos();
	boost::filesystem::path CreateNewDir(const std::string& dirName);
	void CheckExtension(std::string extensionFile);
	std::vector<CDocumentItem>& m_items;
	boost::optional<size_t> m_pos;
	std::shared_ptr<IImage> m_image;	
};
