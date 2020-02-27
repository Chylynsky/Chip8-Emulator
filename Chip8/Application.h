#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <memory>
#include "GUI.h"
#include "GameWindow.h"
#include "Interpreter.h"
#include "KeyboardHandler.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Chip8
{
	class Application
	{
		GUI::Window* window;
		GameWindow* gameWindow;
		Interpreter* interpreter;
		KeyboardHandler keyboardHandler;
		std::wstring romLoadPath;

	public:

		Application();
		~Application();
		void Run();

		void LoadButton_OnClicked();
		void StartButton_OnClicked();
	};
}