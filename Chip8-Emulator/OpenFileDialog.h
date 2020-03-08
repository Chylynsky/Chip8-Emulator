#pragma once
#ifndef WIN32
#define WIN32
#endif

#include <string>
#include <exception>
#include <stdexcept>
#include <FL/Fl_Native_File_Chooser.H>

namespace GUI
{
	// Class responsible for open file dialog creation
	class OpenFileDialog
	{
		Fl_Native_File_Chooser* fileDialog;
		std::string loadPath;

	public:

		OpenFileDialog();
		OpenFileDialog(const std::string& title);
		~OpenFileDialog();
		void Show();
		const std::string& GetFilePath() const;
	};
}