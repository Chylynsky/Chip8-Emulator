#pragma once
#include "Interpreter.h"

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