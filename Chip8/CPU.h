#pragma once
#include <cstdint>
#include "RAM.h"
#include "Registers.h"
#include "Stack.h"
#include "Timer.h"

namespace Chip8
{
	class CPU
	{
		static CPU instance;

		GeneralPurposeRegisters& generalPurposeRegisters;
		RAM& ram;
		Stack& stack;
		uint16_t memoryAddressRegister;
		uint16_t programCounter;

		CPU();

	public:
		
		static CPU& GetInstance();
		void Execute(uint16_t instruction);

		CPU& operator=(const CPU&) = delete;
		CPU& operator=(CPU&&) = delete;
	};
}