#pragma once
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include "CPU.h"
#include "RAM.h"

namespace Chip8
{
	class Interpreter
	{
		static Interpreter instance;

		CPU& cpu;
		RAM& ram;

		Interpreter();

	public:

		static Interpreter& GetInstance();
		void LoadROM(const std::string& loadPath);
	};
}