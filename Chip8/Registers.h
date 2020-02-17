#pragma once
#include <cstdint>

namespace Chip8
{
	enum class RegisterName { V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF };

	class GeneralPurposeRegisters
	{
		static constexpr uint8_t NUMBER_OF_REGISTERS{ 16 };

		static GeneralPurposeRegisters instance;

		uint8_t generalPurposeRegister[NUMBER_OF_REGISTERS];

	public:

		static GeneralPurposeRegisters& GetInstance();

		GeneralPurposeRegisters& operator=(const GeneralPurposeRegisters&) = delete;
		GeneralPurposeRegisters& operator=(GeneralPurposeRegisters&&) = delete;
		uint8_t& operator[](RegisterName registerName);
		uint8_t& operator[](uint8_t registerNumber);
	};
}