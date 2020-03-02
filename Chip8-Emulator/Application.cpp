#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ nullptr }, gameWindow{ nullptr }, interpreter{ nullptr }
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) == -1)
			throw std::runtime_error("Could not initialize SDL2 library.");
		else
		{
			window = new GUI::Window{ 640, 320, "Chip-8 Emulator" };

			try {
				window->SetBackgroundImage("Resources/Title.bmp");
			}
			catch (std::runtime_error & e) {
				GUI::ErrorBox(e.what());
				std::exit(1);
			}

			GUI::Button* loadButton = new GUI::Button{ window, 140, 180, 160, 60 };
			try {
				loadButton->SetIdleImage("Resources/LoadButton.bmp");
				loadButton->SetActiveImage("Resources/LoadButtonActive.bmp");
			}
			catch (std::runtime_error & e) {
				GUI::ErrorBox(e.what());
				std::exit(1);
			}

			loadButton->OnClicked = std::bind(&Application::LoadButton_OnClicked, this);

			GUI::Button* startButton = new GUI::Button{ window, 340, 180, 160, 60 };
			try {
				startButton->SetIdleImage("Resources/StartButton.bmp");
				startButton->SetActiveImage("Resources/StartButtonActive.bmp");
			}
			catch (std::runtime_error & e) {
				GUI::ErrorBox(e.what());
				std::exit(1);
			}

			startButton->OnClicked = std::bind(&Application::StartButton_OnClicked, this);
		}
	}

	Application::~Application()
	{
		delete window;
		window = nullptr;
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
		GUI::OpenFileDialog fileDialog{ "Select ROM" };
		try {
			fileDialog.Show();
			romLoadPath = fileDialog.GetFilePath();
		}
		catch (std::runtime_error & e) {
			GUI::ErrorBox{ e.what() };
			std::exit(1);
		}
	}

	void Application::StartButton_OnClicked()
	{
		if (romLoadPath.empty())
		{
			GUI::WarningBox{ "No ROM loaded!" };
			return;
		}
		else
		{
			std::unique_ptr<GameWindow> gameWindow{ new GameWindow("Chip-8 Emulator") };
			std::unique_ptr<Interpreter>interpreter{ new Interpreter(*gameWindow, keyboardHandler) };
			interpreter->LoadROM(romLoadPath);
			interpreter->Start();

			while (gameWindow->KeepWindowOpen())
			{
				gameWindow->PollEvents(keyboardHandler);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}
}