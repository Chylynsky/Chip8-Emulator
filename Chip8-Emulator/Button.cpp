#include "Button.h"

namespace GUI
{
	bool Button::IsMouseOver(int x, int y)
	{
		if (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height)
			return true;
		else
			return false;
	}

	Button::Button(Window* window, int x, int y, int width, int height) : renderer{ window->renderer }, x { x }, y{ y }, width{ width },
		height{ height }, imageIdle{ nullptr }, imageActive{ nullptr }, imageCurrent{ nullptr }, rect{ x, y, width, height }, OnClicked{ nullptr }
	{
		window->AttachButton(this);
	}

	Button::~Button()
	{
		SDL_DestroyTexture(imageIdle);
		SDL_DestroyTexture(imageActive);
		SDL_DestroyTexture(imageCurrent);
	}

	void Button::Refresh()
	{
		if (imageCurrent != nullptr)
			SDL_RenderCopy(renderer, imageCurrent, nullptr, &rect);
	}

	void Button::ProcessEvent(SDL_Event& e, int x, int y)
	{
		bool isMouseOver = IsMouseOver(x, y);

		if (isMouseOver)
			imageCurrent = imageActive;
		else if (imageIdle)
			imageCurrent = imageIdle;

		if (isMouseOver && e.type == SDL_MOUSEBUTTONDOWN && OnClicked)
			OnClicked();
	}

	void Button::SetIdleImage(std::string loadPath)
	{
		SDL_Surface* surface = SDL_LoadBMP(loadPath.c_str());

		if (!surface)
			throw std::runtime_error("Unable to load " + loadPath + ".");
		else
		{
			imageIdle = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
	}

	void Button::SetActiveImage(std::string loadPath)
	{
		SDL_Surface* surface = SDL_LoadBMP(loadPath.c_str());

		if (!surface)
			throw std::runtime_error("Unable to load " + loadPath + ".");
		else
		{
			imageActive = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
	}
}