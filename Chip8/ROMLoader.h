#pragma once
#include <fstream>
#include <string>
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

		std::ifstream& operator>>(uint8_t& value);
	};
}