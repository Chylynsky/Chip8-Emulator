#include "Window.h"

namespace Chip8
{
	Window::Window(const std::string& title, int width, int height)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw std::runtime_error("Could not initialize window.");
		else
		{
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

			if (!window)
				throw std::runtime_error("An error occured while creating the window.");
			else
			{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

				if (!renderer)
					throw std::runtime_error("An error occured while creating the renderer.");
			}
		}
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
	}

	void Window::RunEventLoop()
	{
		SDL_Event e;

		while (true)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					return;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}