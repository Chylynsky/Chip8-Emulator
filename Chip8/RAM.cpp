#include "RAM.h"

namespace Chip8
{
	RAM RAM::instance{};

	RAM& RAM::GetInstance()
	{
		return instance;
	}

	uint8_t& RAM::operator[](uint16_t address)
	{
		return memory[address];
	}

}