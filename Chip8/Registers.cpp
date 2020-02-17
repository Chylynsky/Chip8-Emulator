#include "Registers.h"

namespace Chip8
{
	GeneralPurposeRegisters GeneralPurposeRegisters::instance{};

	GeneralPurposeRegisters& GeneralPurposeRegisters::GetInstance()
	{
		return instance;
	}

	uint8_t& GeneralPurposeRegisters::operator[](RegisterName registerName)
	{
		return generalPurposeRegister[static_cast<uint8_t>(registerName)];
	}

	uint8_t& GeneralPurposeRegisters::operator[](uint8_t registerNumber)
	{
		return generalPurposeRegister[registerNumber];
	}
}