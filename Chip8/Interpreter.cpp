#include "Interpreter.h"

namespace Chip8
{
	Interpreter::Interpreter(Window& window) : ram{}, delayCounter{}, soundCounter{}, gpu{ window }, cpu{ gpu, ram, delayCounter, soundCounter }, mainClock{ PERIOD }
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

	void Interpreter::LoadROM(const std::wstring& loadPath)
	{
		ram.LoadROM(loadPath);
	}

	void Interpreter::AttachCallbackToMainClock(std::function<void(void)> callback)
	{
		mainClock.AttachCallback(callback);
	}

	void Interpreter::HandleKeyPressed(uint8_t pressedKeyCode)
	{
		cpu.UpdatePressedKeyCode(pressedKeyCode);
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
		gpu.DisplayClear();
		mainClock.Start();
	}
}