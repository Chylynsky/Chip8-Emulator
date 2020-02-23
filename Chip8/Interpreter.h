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
#include "KeyboardHandler.h"

namespace Chip8
{
	class Interpreter
	{
		static constexpr std::chrono::milliseconds PERIOD{ 16 };

		RAM ram;
		Counter delayCounter;
		Counter soundCounter;
		GPU gpu;
		CPU cpu;
		Timer mainClock;
		KeyboardHandler& keyboardHandler;

	public:

		Interpreter(Window& window, KeyboardHandler& keyboardHandler);
		~Interpreter();
		void LoadROM(const std::string& loadPath);
		void LoadROM(const std::wstring& loadPath);
		void Start();
		void Stop();
		void Reset();
	};
}