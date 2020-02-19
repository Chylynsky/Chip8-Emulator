#pragma once
#include <cstdint>
#include <vector>
#include <stack>
#include <mutex>
#include "RAM.h"
#include "Timer.h"
#include "Counters.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Chip8
{
	class CPU
	{
		static constexpr uint8_t NUMBER_OF_REGISTERS{ 16 };

		RAM& ram;
		Counter& delayCounter;
		Counter& soundCounter;
		std::stack<uint16_t> stack;
		std::vector<uint8_t> generalPurposeRegisters;
		uint16_t memoryAddressRegister;
		uint16_t programCounter;

	public:

		std::mutex cpuMutex;
		
		CPU(RAM& ram, Counter& delayCounter, Counter& soundCounter);
		void ExecuteCycle();
		void Reset();

		CPU& operator=(const CPU&) = delete;
		CPU& operator=(CPU&&) = delete;
	};
}