#include "Interpreter.h"

namespace Chip8
{
	Interpreter Interpreter::instance{};

	Interpreter::Interpreter() : cpu{ CPU::GetInstance() }, ram{ RAM::GetInstance() }
	{

	}

	Interpreter& Interpreter::GetInstance()
	{
		return instance;
	}

	void Interpreter::LoadROM(const std::string& loadPath)
	{
		ram.LoadROM(loadPath);
	}
}