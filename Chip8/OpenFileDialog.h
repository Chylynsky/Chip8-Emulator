#pragma once
#include <string>
#include <exception>
#include <stdexcept>
#include "Windows.h"
#include "shobjidl.h"

namespace GUI
{
	class OpenFileDialog
	{
		PWSTR filePath;
		HRESULT hr;
		IFileOpenDialog* dialog;
		IShellItem* selectedItem;

	public:

		OpenFileDialog();
		~OpenFileDialog();
		std::wstring GetFilePath();
	};
}