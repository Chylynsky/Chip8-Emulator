#include "Window.h"

namespace Chip8
{
	Window::Window(const std::string& title)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw std::runtime_error("Could not initialize window.");
		else
		{
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_MAXIMIZED);

			if (!window)
				throw std::runtime_error("An error occured while creating the window.");
			else
			{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

				if (!renderer)
					throw std::runtime_error("An error occured while creating the renderer.");

				SDL_GetWindowSize(window, &Width, &Height);
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

	void Window::ShowErrorBox(const std::string& message)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", message.c_str(), nullptr);
	}

	void Window::AddToRenderQueue(SDL_Rect* texture)
	{
		textures.push(texture);
	}

	void Window::Refresh()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		while (textures.size() > 0)
		{
			SDL_RenderFillRect(renderer, textures.front());
			textures.pop();
		}

		SDL_RenderPresent(renderer);
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

			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
	}
}