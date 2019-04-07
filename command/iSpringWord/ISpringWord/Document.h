#pragma once
#include "History.h"
#include "IDocument.h"

class CDocument : public IDocument
{
public:
	~CDocument();
	void SetTitle(const std::string& title) override;
	std::string GetTitle() const override;

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void Save(const std::string& path) const override;
	void Delete(size_t index) override;

	size_t GetItemsCount() const override;

	std::shared_ptr<IImage> InsertImage(const boost::filesystem::path& path, int width, int height, boost::optional<size_t> position = boost::none) override;
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) override;

	CConstDocumentItem GetItem(size_t index) const override;
	CDocumentItem GetItem(size_t index) override;

private:
	std::string m_title;
	CHistory m_history;
	std::vector<CDocumentItem> m_items;
};