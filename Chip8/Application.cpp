#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ "Chip 8 Emulator" }, interpreter{ window }
	{
		try {
			interpreter.LoadROM("roms/test1.ch8");
		}
		catch (std::runtime_error & e)
		{
			Window::ShowErrorBox(e.what());
			exit(1);
		}
		catch (std::out_of_range & e) {
			Window::ShowErrorBox(e.what());
			exit(1);
		}
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