#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <cstdint>

namespace Chip8
{
	class ROMLoader
	{
		std::ifstream file;

	public:

		ROMLoader(std::string loadPath);
		~ROMLoader();

		template<typename iter>
		void Load(iter where);
		std::ifstream& operator>>(uint8_t& value);
	};

	template<typename iter>
	void ROMLoader::Load(iter where)
	{
		while (!file.eof())
			*(where++) = file.get();
	}
}