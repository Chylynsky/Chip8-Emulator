#include "Window.h"

namespace GUI
{
	void Window::AttachButton(Button* button)
	{
		buttons.push_back(button);
	}

	Window::Window(int x, int y, const std::string& title) : window{ nullptr }, renderer{ nullptr }, backgroundImage{ nullptr }, keepWindowOpen{ true }
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, NULL);

		if (!window)
			throw std::runtime_error("An error occured while creating the window.");
		else
		{
			renderer = SDL_CreateRenderer(window, -1, NULL);

			if (!renderer)
				throw std::runtime_error("An error occured while creating the renderer.");
		}
	}

	Window::~Window()
	{
		for (Button* button : buttons)
			delete button;

		SDL_DestroyTexture(backgroundImage);
		backgroundImage = nullptr;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	void Window::Refresh()
	{
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, backgroundImage, nullptr, nullptr);

		for (auto button : buttons)
		{
			button->Refresh();
		}
		SDL_RenderPresent(renderer);
	}

	void Window::HandleEvents()
	{
		// Procedd events
		SDL_Event e;

		// Mouse position
		int x = 0;
		int y = 0;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				keepWindowOpen = false;
			}

			SDL_GetMouseState(&x, &y);
			for (auto button : buttons)
			{
				button->ProcessEvent(e, x, y);
			}
		}
	}

	void Window::SetBackgroundImage(std::string loadPath)
	{
		SDL_Surface* surface = SDL_LoadBMP(loadPath.c_str());

		if (!surface)
			throw std::runtime_error("Unable to load " + loadPath + ".");
		else
		{
			backgroundImage = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
	}

	bool Window::KeepWindowOpen()
	{
		return keepWindowOpen;
	}
}