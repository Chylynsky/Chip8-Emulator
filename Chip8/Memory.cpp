#include "Memory.h"

namespace Chip8
{
	Memory Memory::instance{ };

	Memory& Memory::GetInstance()
	{
		return instance;
	}

	uint8_t& Memory::operator[](uint16_t memoryAddress)
	{
		return memory[memoryAddress];
	}

}