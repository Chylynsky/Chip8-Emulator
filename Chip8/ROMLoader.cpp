#include "ROMLoader.h"

namespace Chip8
{
	ROMLoader::ROMLoader(std::string loadPath)
	{
		file.open(loadPath, std::ios::binary);

		if (!file.is_open())
			throw std::runtime_error("File " + loadPath + " could not be opened.");
	}

	ROMLoader::~ROMLoader()
	{
		file.close();
	}
}