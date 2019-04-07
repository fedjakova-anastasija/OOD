#pragma once
#include "AbstractCommand.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& width, int const& newWidth, int& height, int const& newHeight);
	
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	int& m_height;
	int m_newHeight;
	int& m_width;
	int m_newWidth;
};
