#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ nullptr }, gameWindow{ nullptr }, interpreter{ nullptr }
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw std::runtime_error("Could not initialize SDL2 library.");
		else
		{
			window = new Window{ 640, 320, "Chip-8 Emulator" };
			window->SetBackgroundImage("Resources/Title.bmp");

			Button* loadButton = new Button{ window, 140, 180, 160, 60 };
			loadButton->SetIdleImage("Resources/LoadButton.bmp");
			loadButton->SetActiveImage("Resources/LoadButtonActive.bmp");
			loadButton->OnClicked = std::bind(&Application::LoadButton_OnClicked, this);

			Button* startButton = new Button{ window, 340, 180, 160, 60 };
			startButton->SetIdleImage("Resources/StartButton.bmp");
			startButton->SetActiveImage("Resources/StartButtonActive.bmp");
			startButton->OnClicked = std::bind(&Application::StartButton_OnClicked, this);
		}
	}

	Application::~Application()
	{
		delete interpreter;
		delete gameWindow;
		delete window;
		SDL_Quit();
	}

	void Application::Run()
	{
		while (window->KeepWindowOpen())
		{
			window->Refresh();
			window->HandleEvents();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}

	void Application::LoadButton_OnClicked()
	{
		try {
#ifdef _WIN32
			OpenFileDialog dialog;
			romLoadPath = dialog.GetFilePath();
#else
			std::string loadPath;
			std::cout << "Enter Chip 8 ROM file path: "
				std::cin >> loadPath;
			interpreter.LoadROM(loadPath);
			std::cout << std::endl;
#endif
		}
		catch (std::runtime_error & e)
		{
#ifdef _DEBUG
			std::cerr << e.what() << std::endl;
#endif
			GameWindow::ShowErrorBox(e.what());
			exit(1);
		}
		catch (std::out_of_range & e) {
#ifdef _DEBUG
			std::cerr << e.what() << std::endl;
#endif
			GameWindow::ShowErrorBox(e.what());
			exit(1);
		}
	}

	void Application::StartButton_OnClicked()
	{
		gameWindow = new GameWindow("Chip-8 Emulator");
		interpreter = new Interpreter(*gameWindow, keyboardHandler);
		interpreter->LoadROM(romLoadPath);
		interpreter->Start();

		while (gameWindow->KeepWindowOpen())
		{
			gameWindow->PollEvents(keyboardHandler);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		delete interpreter;
		interpreter = nullptr;
		delete gameWindow;
		gameWindow = nullptr;
	}
}