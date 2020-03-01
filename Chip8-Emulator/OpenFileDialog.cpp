#include "OpenFileDialog.h"

namespace GUI
{
	OpenFileDialog::OpenFileDialog() : fileDialog{ new Fl_Native_File_Chooser }
	{
		fileDialog->type(Fl_Native_File_Chooser::BROWSE_FILE);
		fileDialog->title("Pick a file");
	}

	OpenFileDialog::OpenFileDialog(const std::string& title) : fileDialog{ new Fl_Native_File_Chooser }
	{
		fileDialog->type(Fl_Native_File_Chooser::BROWSE_FILE);
		fileDialog->title(title.c_str());
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

	std::string OpenFileDialog::GetFilePath()
	{
		return loadPath;
	}
}