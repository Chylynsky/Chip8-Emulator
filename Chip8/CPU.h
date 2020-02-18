#pragma once
#include <cstdint>
#include <stack>
#include <mutex>
#include "RAM.h"
#include "Timer.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Chip8
{
	class CPU
	{
		static constexpr uint8_t NUMBER_OF_REGISTERS{ 16 };

		static CPU instance;

		RAM& ram;
		std::stack<uint16_t> stack;
		uint8_t generalPurposeRegisters[NUMBER_OF_REGISTERS];
		uint16_t memoryAddressRegister;
		uint16_t programCounter;

		CPU();

	public:
		
		static CPU& GetInstance();
		void ExecuteCycle();
		void Reset();

		CPU& operator=(const CPU&) = delete;
		CPU& operator=(CPU&&) = delete;
	};
}