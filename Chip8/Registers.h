#pragma once
#include <cstdint>

namespace Chip8
{
	enum class RegisterName { V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF };

	class Registers
	{
		static constexpr uint8_t NUMBER_OF_REGISTERS{ 16 };
		static Registers instance;

		uint8_t dataRegister[NUMBER_OF_REGISTERS];

	public:

		static Registers& GetInstance();

		Registers& operator=(const Registers&) = delete;
		Registers& operator=(Registers&&) = delete;
		uint8_t& operator[](RegisterName registerName);
		uint8_t& operator[](uint8_t registerNumber);
	};
}