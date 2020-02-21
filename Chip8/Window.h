#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <exception>
#include <stdexcept>
#include "SDL.h"

namespace Chip8
{
	class Window
	{
		SDL_Window* window;
		SDL_Renderer* renderer;

	public:

		Window(const std::string& title, int width, int height);
		~Window();

		void RunEventLoop();
	};
}