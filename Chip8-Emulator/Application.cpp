#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ nullptr }, gameWindow{ nullptr }, interpreter{ nullptr }
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) == -1)
		{
			GUI::ErrorBox{ "Could not initialize SDL2 library." };
			std::exit(1);
		}
		else
		{
			try {
				// Create window
				window = new GUI::Window{ 640, 320, "Chip-8 Emulator" };
				window->SetBackgroundImage("Resources/Title.bmp");
			}
			catch (std::runtime_error & e) {
				GUI::ErrorBox(e.what());
				std::exit(1);
			}

			// Create buttons
			GUI::Button* loadButton = new GUI::Button{ window, 140, 180, 160, 60 };
			try {
				loadButton->SetIdleImage("Resources/LoadButton.bmp");
				loadButton->SetActiveImage("Resources/LoadButtonActive.bmp");
			}
			catch (std::runtime_error & e) {
				GUI::ErrorBox(e.what());
				std::exit(1);
			}
			// Attach callback
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
			// Attach callback
			startButton->OnClicked = std::bind(&Application::StartButton_OnClicked, this);
		}
	}

	Application::~Application()
	{
		delete window;
		window = nullptr;
		SDL_Quit();
	}

	// Run the GUI
	void Application::Run()
	{
		while (window->KeepWindowOpen())
		{
			window->Refresh();
			window->HandleEvents();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}

	// Open the file dialog and save the selected files path to romLoadPath
	void Application::LoadButton_OnClicked()
	{
		GUI::OpenFileDialog fileDialog{ "*.ch8", "Select ROM" };
		try {
			fileDialog.Show();
		}
		catch (std::runtime_error & e) {
			GUI::ErrorBox{ e.what() };
			std::exit(1);
		}
		romLoadPath = fileDialog.GetFilePath();
	}

	// If ROM file is selected, load it to memory and run the interpreter
	void Application::StartButton_OnClicked()
	{
		if (romLoadPath.empty())
		{
			GUI::WarningBox{ "No ROM loaded!" };
			return;
		}
		else
		{
			std::unique_ptr<GameWindow> gameWindow{ std::make_unique<GameWindow>("Chip-8 Emulator") };
			std::unique_ptr<Interpreter>interpreter{ std::make_unique<Interpreter>(*gameWindow, keyboardHandler) };
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