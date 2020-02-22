#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include "Window.h"
#include "Interpreter.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace Chip8
{
	class Application
	{
		Window window;
		Interpreter interpreter;

	public:

		Application();
		~Application();
		void Run();
	};
}