#pragma once
#include <string>
#include <vector>
#include <functional>
#include "SDL.h"
#include "Window.h"

namespace GUI
{
	class Window;

	// Button class.
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

		// Check if the [x, y] coordinates are inside the button
		bool IsMouseOver(int x, int y);

	public:

		std::function<void(void)> OnClicked;

		Button(Window* window, int x, int y, int width, int height);
		~Button();

		// Buttons should be refreshed to display their current state, function is called by the parent window
		void Refresh();
		// React to the mouse events
		// e - processed event 
		// {x, y} - current mouse position
		void ProcessEvent(SDL_Event& e, int x, int y);
		// Attach image that is displayed when button is in idle state
		void SetIdleImage(std::string loadPath);
		// Attach image that is displayed when button is in active state
		void SetActiveImage(std::string loadPath);
	};
}