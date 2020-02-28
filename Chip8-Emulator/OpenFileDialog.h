#pragma once
#include <string>
#include <exception>
#include <stdexcept>
//#include "FL/Fl_Native_File_Chooser.H"

namespace GUI
{
	class OpenFileDialog
	{



	public:

		OpenFileDialog();
		~OpenFileDialog();
		std::wstring GetFilePath();
	};
}