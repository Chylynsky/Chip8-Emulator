#pragma once
#include <string>
#include <vector>
#include <functional>
#include "SDL.h"
#include "Window.h"

namespace GUI
{
	class Window;

	// Buttons have two states represented by two seperate images - Idle and Active
	class Button
	{
		SDL_Renderer* renderer;
		int x;
		int y;
		int width;
		int height;
		SDL_Texture* imageIdle;
		SDL_Texture* imageActive;
		SDL_Texture* imageCurrent;
		SDL_Rect rect;

		bool IsMouseOver(int x, int y);

	public:

		std::function<void(void)> OnClicked;

		Button(Window* window, int x, int y, int width, int height);
		~Button();

		void Refresh();
		// e - processed event 
		// {x, y} - current mouse position
		void ProcessEvent(SDL_Event& e, int x, int y);
		void SetIdleImage(std::string loadPath);
		void SetActiveImage(std::string loadPath);
	};
}