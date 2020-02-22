#pragma once
#include <cstdint>
#include <array>
#include <stack>
#include <mutex>
#include <random>
#include <limits>
#include <sstream>
#include "GPU.h"
#include "RAM.h"
#include "Counters.h"

#ifdef _DEBUG
#include <iostream>
#endif

#undef min
#undef max

namespace Chip8
{
	class CPU
	{
		static constexpr uint8_t NUMBER_OF_REGISTERS{ 16 };

		GPU& gpu;
		RAM& ram;
		Counter& delayCounter;
		Counter& soundCounter;
		std::stack<uint16_t> stack;
		std::array<uint8_t, NUMBER_OF_REGISTERS> generalPurposeRegisters;
		uint16_t memoryAddressRegister;
		uint16_t programCounter;

		// Random numbers generation
		std::default_random_engine randomEngine;
		std::uniform_int_distribution<int> Random;

	public:

		std::mutex cpuMutex;
		
		CPU(GPU& gpu, RAM& ram, Counter& delayCounter, Counter& soundCounter);
		~CPU();
		void ExecuteCycle();
		void Reset();

		CPU& operator=(const CPU&) = delete;
		CPU& operator=(CPU&&) = delete;
	};
}