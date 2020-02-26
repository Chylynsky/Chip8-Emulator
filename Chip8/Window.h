#pragma once
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <functional>
#include "SDL.h"
#include "Button.h"

namespace GUI
{
	class Button;

	class Window
	{
		friend class Button;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* backgroundImage;
		std::vector<Button*> buttons;
		bool keepWindowOpen;

		void AttachButton(Button* button);

	public:

		Window(int x, int y, const std::string& title);
		~Window();

		void Refresh();
		void HandleEvents();
		void SetBackgroundImage(std::string loadPath);
		bool KeepWindowOpen();
	};
}