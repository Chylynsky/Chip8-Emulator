#pragma once
#include <string>
#include <queue>
#include <exception>
#include <stdexcept>
#include "SDL.h"
#include "KeyboardHandler.h"

namespace Chip8
{
	class GameWindow
	{
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::queue<SDL_Rect> pixels;
		bool keepWindowOpen;

	public:

		int Width;
		int Height;

		GameWindow(const std::string& title);
		~GameWindow();

		void AddToRenderQueue(SDL_Rect texture);
		void Refresh();
		void PollEvents(KeyboardHandler& keyboardHandler);
		bool KeepWindowOpen();
	};
}