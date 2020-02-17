#include "RAM.h"

namespace Chip8
{
	RAM RAM::instance{};

	RAM& RAM::GetInstance()
	{
		return instance;
	}

	void RAM::LoadFile(const std::string& loadPath)
	{
		ROMLoader loader{ loadPath };
		int address = 0x200; // Start at memory address of 0x200

		while (loader >> memory[address])
			address++;
	}

	uint8_t& RAM::operator[](uint16_t address)
	{
		return memory[address];
	}

}