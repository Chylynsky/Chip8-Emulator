#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <cstdint>

namespace Chip8
{
	// Class taking care of loading *.ch8 files to the memory
	class ROMLoader
	{
		std::ifstream file;

	public:

		ROMLoader(std::string loadPath);
		ROMLoader(std::wstring loadPath);
		~ROMLoader();

		template<typename iter>
		void Load(iter first, const iter last);
	};

	// Pass the loaded *ch8 file to the specified container.
	template<typename iter>
	void ROMLoader::Load(iter first, const iter last)
	{
		while (!file.eof())
		{
			if (first == last)
				throw std::out_of_range("Loaded file caused memory corruption.");

			*(first++) = file.get();
		}
	}
}