#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ "Chip 8 Emulator" }, interpreter{ window, keyboardHandler }
	{
	}

	Application::~Application()
	{
		interpreter.Stop();
	}

	void Application::Run()
	{
		//window.Refresh();

		try {
#ifdef _WIN32
			OpenFileDialog dialog;
			interpreter.LoadROM(dialog.GetFilePath());
#else
			std::string loadPath;
			std::cout << "Enter Chip 8 ROM file path: "
			std::cin >> loadPath;
			interpreter.LoadROM(loadPath);
			std::cout << std::endl;
#endif
			window.Show();
			interpreter.Start();
		}
		catch (std::runtime_error & e)
		{
#ifdef _DEBUG
			std::cerr << e.what() << std::endl;
#endif
			Window::ShowErrorBox(e.what());
			exit(1);
		}
		catch (std::out_of_range & e) {
#ifdef _DEBUG
			std::cerr << e.what() << std::endl;
#endif
			Window::ShowErrorBox(e.what());
			exit(1);
		}

		while (window.KeepWindowOpen())
		{
			window.PollEvents(keyboardHandler);
			std::this_thread::sleep_for(std::chrono::microseconds(600));
		}
	}
}