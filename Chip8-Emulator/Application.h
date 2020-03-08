#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <memory>
#include "GUI.h"
#include "GameWindow.h"
#include "Interpreter.h"
#include "KeyboardHandler.h"
#include "OpenFileDialog.h"

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
		void Run();

		void LoadButton_OnClicked();
		void StartButton_OnClicked();
	};
}