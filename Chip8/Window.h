#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <queue>
#include <exception>
#include <stdexcept>
#include "SDL.h"

namespace Chip8
{
	class Window
	{
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::queue<SDL_Rect*> textures;

	public:

		int Width;
		int Height;

		Window(const std::string& title);
		~Window();

		static void ShowErrorBox(const std::string& message);

		void AddToRenderQueue(SDL_Rect* texture);
		void Refresh();
		void RunEventLoop();
	};
}