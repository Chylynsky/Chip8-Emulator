#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ "Chip 8 Emulator", scale * width, scale * height }, interpreter{ window }
	{
		interpreter.LoadROM("roms/test1.ch8");
	}

	Application::~Application()
	{
		interpreter.Stop();
	}

	void Application::Run()
	{
		interpreter.Start();
		window.RunEventLoop();
	}
}