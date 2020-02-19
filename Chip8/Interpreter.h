#pragma once
#include <cstdint>
#include <string>
#include <chrono>
#include <exception>
#include <stdexcept>
#include <functional>
#include "CPU.h"
#include "RAM.h"
#include "Timer.h"
#include "Counters.h"

namespace Chip8
{
	class Interpreter
	{
		static constexpr std::chrono::milliseconds PERIOD{ 100 };

		RAM ram;
		Counter delayCounter;
		Counter soundCounter;
		CPU cpu;
		Timer mainClock;

	public:

		Interpreter();
		~Interpreter();
		void LoadROM(const std::string& loadPath);
		void Start();
		void Stop();
		void Reset();

		Interpreter& operator=(const Interpreter&) = delete;
		Interpreter& operator=(Interpreter&&) = delete;
	};
}