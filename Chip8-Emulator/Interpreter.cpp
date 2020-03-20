#include "Interpreter.h"

namespace Chip8
{
	Interpreter::Interpreter(GameWindow& window, KeyboardHandler& keyboardHandler) : ram{}, delayCounter{ 8 }, soundCounter{ 8 }, gpu{ window }, 
		cpu{ gpu, ram, delayCounter, soundCounter, keyboardHandler }, mainClock{ MAIN_CLOCK_PERIOD }, tonePlayer{ 220.0f }, keyboardHandler{ keyboardHandler }
	{
		// Attach main clock callbacks
		mainClock.AttachCallback(std::bind(&Counter::Decrement, &delayCounter));
		mainClock.AttachCallback(std::bind(&Counter::Decrement, &soundCounter));
		mainClock.AttachCallback(std::bind(&CPU::ExecuteCycle, &cpu));

		// Attach counter callbacks
		soundCounter.CountingOn = std::bind(&TonePlayer::Play, &tonePlayer);
		soundCounter.CountingFinished = std::bind(&TonePlayer::Stop, &tonePlayer);
	}

	Interpreter::~Interpreter()
	{
		mainClock.Stop();
	}

	// Load ROM file into virtual RAM memory
	void Interpreter::LoadROM(const std::string& loadPath)
	{
		ram.LoadROM(loadPath);
	}

	// Load ROM file into virtual RAM memory
	void Interpreter::LoadROM(const std::wstring& loadPath)
	{
		ram.LoadROM(loadPath);
	}

	// Run the loaded program
	void Interpreter::Start()
	{
		mainClock.Start();
	}

	// Stop the execution
	void Interpreter::Stop()
	{
		mainClock.Stop();
	}

	// Start from the beginning
	void Interpreter::Reset()
	{
		cpu.Reset();
		ram.ClearProgramMemory();
		gpu.DisplayClear();
	}
}