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
		static Interpreter instance;

		Timer mainClock;
		CPU& cpu;
		RAM& ram;
		DelayCounter& delayCounter;
		SoundCounter& soundCounter;

		Interpreter();
		~Interpreter();

	public:

		static Interpreter& GetInstance();
		void LoadROM(const std::string& loadPath);
		void Start();
		void Stop();
		void Reset();

		Interpreter& operator=(const Interpreter&) = delete;
		Interpreter& operator=(Interpreter&&) = delete;
	};
}