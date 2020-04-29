#include "Application.h"

namespace Chip8
{
	Application::Application() : window{ nullptr }, gameWindow{ nullptr }, interpreter{ nullptr }
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) == -1)
		{
#ifdef _DEBUG
			std::cerr << "Could not initialize SDL2 library." << std::endl;
#endif
			GUI::ErrorBox errorBox{ "Could not initialize SDL2 library." };
			std::exit(1);
		}
		else
		{
			try {
				// Create window
				window = new GUI::Window{ 640, 320, "Chip-8 Emulator" };
				window->SetBackgroundImage("Resources/Title.bmp");
			}
			catch (const std::runtime_error & e) {
#ifdef _DEBUG
				std::cerr << e.what() << std::endl;
#endif
				GUI::ErrorBox errorBox(e.what());
				std::exit(1);
			}

			// Create buttons
			GUI::Button* loadButton = new GUI::Button{ window, 140, 180, 160, 60 };
			try {
				loadButton->SetIdleImage("Resources/LoadButton.bmp");
				loadButton->SetActiveImage("Resources/LoadButtonActive.bmp");
			}
			catch (const std::runtime_error & e) {
#ifdef _DEBUG
				std::cerr << e.what() << std::endl;
#endif
				GUI::ErrorBox errorBox(e.what());
				std::exit(1);
			}
			// Attach callback
			loadButton->OnClicked = std::bind(&Application::LoadButton_OnClicked, this);

			GUI::Button* startButton = new GUI::Button{ window, 340, 180, 160, 60 };
			try {
				startButton->SetIdleImage("Resources/StartButton.bmp");
				startButton->SetActiveImage("Resources/StartButtonActive.bmp");
			}
			catch (const std::runtime_error & e) {
#ifdef _DEBUG
				std::cerr << e.what() << std::endl;
#endif
				GUI::ErrorBox errorBox(e.what());
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
		catch (const std::runtime_error & e) {
#ifdef _DEBUG
			std::cerr << e.what() << std::endl;
#endif
			GUI::ErrorBox errorBox{ e.what() };
			std::exit(1);
		}
		romLoadPath = fileDialog.GetFilePath();
	}

	// If ROM file is selected, load it to memory and run the interpreter
	void Application::StartButton_OnClicked()
	{
		if (romLoadPath.empty())
		{
#ifdef _DEBUG
			std::cerr << "No ROM loaded!" << std::endl;
#endif
			GUI::WarningBox errorBox{ "No ROM loaded!" };
			return;
		}
		else
		{
			std::unique_ptr<GameWindow> gameWindow{ std::make_unique<GameWindow>("Chip-8 Emulator") };
			std::unique_ptr<Interpreter>interpreter{ std::make_unique<Interpreter>(*gameWindow, keyboardHandler) };

			try {
				interpreter->LoadROM(romLoadPath);
			}
			catch (const std::exception & e) {
#ifdef _DEBUG
				std::cerr << e.what() << std::endl;
#endif
				interpreter->Reset();
				GUI::ErrorBox errorBox{ e.what() };
				return;
			}

			interpreter->Start();

			while (gameWindow->KeepWindowOpen())
			{
				gameWindow->PollEvents(keyboardHandler);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}
}