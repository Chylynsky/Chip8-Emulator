#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <memory>
#include "GUI.h"
#include "GameWindow.h"
#include "Interpreter.h"
#include "KeyboardHandler.h"

namespace Chip8
{
	// Main class, controlls the execution of the program as well as main window looks
	class Application
	{
		GUI::Window* window;
		GameWindow* gameWindow;
		Interpreter* interpreter;
		KeyboardHandler keyboardHandler;
		std::string romLoadPath;

	public:

		Application();
		~Application();

		// Run the GUI
		void Run();
		// Open the file dialog and save the selected files path to romLoadPath
		void LoadButton_OnClicked();
		// If ROM file is selected, load it to memory and run the interpreter
		void StartButton_OnClicked();
	};
}