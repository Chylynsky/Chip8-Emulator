#include "Interpreter.h"

namespace Chip8
{
	Interpreter::Interpreter(GameWindow& window, KeyboardHandler& keyboardHandler) : ram{}, delayCounter{}, soundCounter{}, gpu{ window }, 
		cpu{ gpu, ram, delayCounter, soundCounter, keyboardHandler }, mainClock{ MAIN_CLOCK_PERIOD }, audioFile{ "Resources/tone.wav" }, keyboardHandler{ keyboardHandler }
	{
		mainClock.AttachCallback(std::bind(&Counter::Decrement, &delayCounter));
		mainClock.AttachCallback(std::bind(&Counter::Decrement, &soundCounter));
		mainClock.AttachCallback(std::bind(&CPU::ExecuteCycle, &cpu));

		soundCounter.CountingOn = std::bind(&AudioFile::Play, &audioFile);
		soundCounter.CountingOn = std::bind(&AudioFile::Pause, &audioFile);
	}

	Interpreter::~Interpreter()
	{
		mainClock.Stop();
	}

	void Interpreter::LoadROM(const std::string& loadPath)
	{
		ram.LoadROM(loadPath);
	}

	void Interpreter::LoadROM(const std::wstring& loadPath)
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
		cpu.Reset();
		ram.ClearProgramMemory();
		gpu.DisplayClear();
	}
}