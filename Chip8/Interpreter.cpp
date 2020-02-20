#include "Interpreter.h"

namespace Chip8
{
	Interpreter::Interpreter() : ram{}, delayCounter{}, soundCounter{}, cpu{ ram, delayCounter, soundCounter }, mainClock{ PERIOD }
	{
		mainClock.AttachCallback(std::bind(&Counter::Decrement, &delayCounter));
		mainClock.AttachCallback(std::bind(&Counter::Decrement, &soundCounter));
		mainClock.AttachCallback(std::bind(&CPU::ExecuteCycle, &cpu));
	}

	Interpreter::~Interpreter()
	{
		mainClock.Stop();
	}

	void Interpreter::LoadROM(const std::string& loadPath)
	{
		ram.LoadROM(loadPath);
	}

	void Interpreter::Start()
	{
		mainClock.Start();
	}

	void Interpreter::Stop()
	{
		mainClock.Stop();
	}

	void Interpreter::Reset()
	{
		mainClock.Stop();
		cpu.Reset();
		mainClock.Start();
	}
}