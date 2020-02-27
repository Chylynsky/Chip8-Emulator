#include "OpenFileDialog.h"

namespace GUI
{
	OpenFileDialog::OpenFileDialog() : filePath{ nullptr }, hr{ 0 }, dialog{ nullptr }, selectedItem{ nullptr }
	{
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&dialog));

			if (SUCCEEDED(hr))
			{
				hr = dialog->Show(nullptr);

				if (SUCCEEDED(hr))
				{
					hr = dialog->GetResult(&selectedItem);

					if (SUCCEEDED(hr))
					{
						selectedItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
					}
					else
						throw std::runtime_error("An error occured while getting results from file dialog.");
				}
				else
					throw std::runtime_error("No file selected.");
			}
		}
	}

	OpenFileDialog::~OpenFileDialog()
	{
		selectedItem->Release();
		dialog->Release();
		CoUninitialize();
	}

	std::wstring OpenFileDialog::GetFilePath()
	{
		if (!filePath)
			return std::wstring();
		else
			return filePath;
	}
}