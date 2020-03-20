#include "ROMLoader.h"

namespace Chip8
{
	ROMLoader::ROMLoader(std::string loadPath)
	{
		file.open(loadPath, std::ios::binary);

		if (!file.is_open()) {
#ifdef _DEBUG
			std::cerr << "File " + loadPath + " could not be opened." << std::endl;
#endif
			throw std::runtime_error("File " + loadPath + " could not be opened.");
		}
	}

	ROMLoader::ROMLoader(std::wstring loadPath)
	{
		file.open(loadPath, std::ios::binary);

		if (!file.is_open()) {
#ifdef _DEBUG
			std::wcerr << L"File " + loadPath + L" could not be opened." << std::endl;
#endif
			throw std::runtime_error("File could not be opened.");
		}
	}

	ROMLoader::~ROMLoader()
	{
		file.close();
	}
}