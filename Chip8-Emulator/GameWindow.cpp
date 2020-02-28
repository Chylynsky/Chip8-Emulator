#include "GameWindow.h"

namespace Chip8
{
	GameWindow::GameWindow(const std::string& title) : keepWindowOpen{ true }
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_MAXIMIZED);

		if (!window)
			throw std::runtime_error("An error occured while creating the window.");
		else
		{
			renderer = SDL_CreateRenderer(window, -1, NULL);

			if (!renderer)
				throw std::runtime_error("An error occured while creating the renderer.");

			SDL_GetWindowSize(window, &Width, &Height);
		}
	}

	GameWindow::~GameWindow()
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	void GameWindow::AddToRenderQueue(SDL_Rect texture)
	{
		pixels.push(texture);
	}

	void GameWindow::Refresh()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		while (pixels.size() > 0)
		{
			SDL_RenderFillRect(renderer, &pixels.front());
			pixels.pop();
		}

		SDL_RenderPresent(renderer);
	}

	void GameWindow::PollEvents(KeyboardHandler& keyboardHandler)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				keepWindowOpen = false;
			}
			else if (e.type == SDL_KEYUP)
			{
				keyboardHandler.NoKeyPressed();
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_0:
					keyboardHandler.KeyPressed(0x0);
					break;
				case SDLK_1:
					keyboardHandler.KeyPressed(0x1);
					break;
				case SDLK_2:
					keyboardHandler.KeyPressed(0x2);
					break;
				case SDLK_3:
					keyboardHandler.KeyPressed(0x3);
					break;
				case SDLK_4:
					keyboardHandler.KeyPressed(0x4);
					break;
				case SDLK_5:
					keyboardHandler.KeyPressed(0x5);
					break;
				case SDLK_6:
					keyboardHandler.KeyPressed(0x6);
					break;
				case SDLK_7:
					keyboardHandler.KeyPressed(0x7);
					break;
				case SDLK_8:
					keyboardHandler.KeyPressed(0x8);
					break;
				case SDLK_9:
					keyboardHandler.KeyPressed(0x9);
					break;
				case SDLK_a:
					keyboardHandler.KeyPressed(0xA);
					break;
				case SDLK_b:
					keyboardHandler.KeyPressed(0xB);
					break;
				case SDLK_c:
					keyboardHandler.KeyPressed(0xC);
					break;
				case SDLK_d:
					keyboardHandler.KeyPressed(0xD);
					break;
				case SDLK_e:
					keyboardHandler.KeyPressed(0xE);
					break;
				case SDLK_f:
					keyboardHandler.KeyPressed(0xF);
					break;
				case SDLK_ESCAPE:
					keepWindowOpen = false;
					break;
				default: 
					break;
				}
			}
		}
	}

	void GameWindow::Show()
	{
		SDL_ShowWindow(window);
	}

	void GameWindow::Hide()
	{
		SDL_HideWindow(window);
	}

	void GameWindow::Maximize()
	{
		SDL_MaximizeWindow(window);
	}

	void GameWindow::Minimize()
	{
		SDL_MinimizeWindow(window);
	}

	bool GameWindow::KeepWindowOpen()
	{
		return keepWindowOpen;
	}
}