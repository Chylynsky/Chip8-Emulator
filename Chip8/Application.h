#pragma once
#include "Interpreter.h"

namespace Chip8
{
	class Application
	{
		// Resolution
		static const int width{ 64 };
		static const int height{ 32 };
		static const int scale{ 10 };

		Window window;
		Interpreter interpreter;

	public:

		Application();
		~Application();
		void Run();
	};
}