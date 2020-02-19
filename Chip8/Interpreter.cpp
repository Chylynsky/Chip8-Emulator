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
#ifndef _DEBUG
		ram.LoadROM(loadPath);
#endif
#ifdef _DEBUG
		try {
			ram.LoadROM(loadPath);
			std::cout << "Rom " + loadPath + " succesfully loaded into RAM." << std::endl;
		}
		catch (std::runtime_error & e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
#endif
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