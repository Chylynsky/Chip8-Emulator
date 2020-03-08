#include "OpenFileDialog.h"

namespace GUI
{
	OpenFileDialog::OpenFileDialog(const std::string& filter, const std::string& title) : fileDialog{ new Fl_Native_File_Chooser }
	{
		fileDialog->type(Fl_Native_File_Chooser::BROWSE_FILE);
		fileDialog->title(title.c_str());
		fileDialog->filter(filter.c_str());
	}

	OpenFileDialog::~OpenFileDialog()
	{
		delete fileDialog;
	}

	void OpenFileDialog::Show()
	{
		switch (fileDialog->show())
		{
		case -1:
			throw std::runtime_error(fileDialog->errmsg());
			break;
		case 1:
			break;
		default: loadPath = fileDialog->filename();
		}
	}

	const std::string& OpenFileDialog::GetFilePath() const
	{
		return loadPath;
	}
}