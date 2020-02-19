#include "RAM.h"

namespace Chip8
{
	RAM::RAM() : memory{ std::vector<uint8_t>(MEMORY_CAPACITY) }
	{

	}

	void RAM::LoadROM(const std::string& loadPath)
	{
		ROMLoader loader{ loadPath }; // May throw

		int address = 0x200; // Start at memory address of 0x200

		std::lock_guard<std::mutex> ramGuard{ ramMutex };

		while (loader >> memory[address])
			address++;
	}

	uint8_t& RAM::operator[](uint16_t address)
	{
		return memory[address];
	}

}