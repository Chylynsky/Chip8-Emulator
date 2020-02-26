#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include "GUI.h"
#include "GameWindow.h"
#include "Interpreter.h"
#include "KeyboardHandler.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Chip8
{
	using namespace GUI;

	class Application
	{
		Window* window;
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