#include "Registers.h"

namespace Chip8
{
	Registers Registers::instance{ };

	Registers& Registers::GetInstance()
	{
		return instance;
	}
	uint8_t& Registers::operator[](RegisterName registerName)
	{
		return dataRegister[static_cast<uint8_t>(registerName)];
	}
	uint8_t& Registers::operator[](uint8_t registerNumber)
	{
		return dataRegister[registerNumber];
	}
}