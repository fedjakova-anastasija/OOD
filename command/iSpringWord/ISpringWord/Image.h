#pragma once
#include "ICommandHistory.h"
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(const boost::filesystem::path& path, int width, int height, ICommandHistory& history);

	boost::filesystem::path GetPath() const override;

	// Ширина изображения в пикселях
	int GetWidth() const override;

	// Высота изображения в пикселях
	int GetHeight() const override;

	// Изменяет размер изображения
	void Resize(int width, int height) override;

private:
	boost::filesystem::path m_path;
	int m_width;
	int m_height;
	ICommandHistory& m_history;
	
	void CheckPath(const boost::filesystem::path& path);
};
