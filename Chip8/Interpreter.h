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
#include "Window.h"

namespace Chip8
{
	class Interpreter
	{
		static constexpr std::chrono::milliseconds PERIOD{ 10 };

		RAM ram;
		Counter delayCounter;
		Counter soundCounter;
		GPU gpu;
		CPU cpu;
		Timer mainClock;

	public:

		Interpreter(Window& window);
		~Interpreter();
		void LoadROM(const std::string& loadPath);
		void AttachCallbackToMainClock(std::function<void(void)> callback);
		void Start();
		void Stop();
		void Reset();

		Interpreter& operator=(const Interpreter&) = delete;
		Interpreter& operator=(Interpreter&&) = delete;
	};
}