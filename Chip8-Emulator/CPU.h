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
#include "KeyboardHandler.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Chip8
{
	// CPU class handles Chip8 CPU emulation
	class CPU
	{
		// Number of general purpose registers
		static constexpr uint8_t NUMBER_OF_REGISTERS{ 16 };

		// CPU connections with peripheral "hardware"
		//
		GPU& gpu;
		RAM& ram;
		Counter& delayCounter;
		Counter& soundCounter;
		KeyboardHandler& keyboardHandler;
		//

		// Internal CPU logic
		//
		std::stack<uint16_t> stack;
		std::array<uint8_t, NUMBER_OF_REGISTERS> generalPurposeRegisters;
		uint16_t memoryAddressRegister;
		uint16_t programCounter;
		//

		// Random numbers generation
		std::default_random_engine randomEngine;
		std::uniform_int_distribution<int> Random;

		std::mutex cpuMutex;

	public:
		
		CPU(GPU& gpu, RAM& ram, Counter& delayCounter, Counter& soundCounter, KeyboardHandler& keyboardHandler);
		~CPU();

		// Execute one instruction specified by the programCounter
		void ExecuteCycle();
		// Clear the registers and set the program counter to the beginning
		void Reset();

		CPU& operator=(const CPU&) = delete;
		CPU& operator=(CPU&&) = delete;
	};
}