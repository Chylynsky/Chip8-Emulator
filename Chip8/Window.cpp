#include "Window.h"

namespace Chip8
{
	Window::Window(const std::string& title) : title{ title }, keepWindowOpen{ true }
	{  
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw std::runtime_error("Could not initialize SDL2 library.");
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

	void Window::AddToRenderQueue(SDL_Rect texture)
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
			SDL_RenderFillRect(renderer, &textures.front());
			textures.pop();
		}

		SDL_RenderPresent(renderer);
	}

	void Window::PollEvents()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				keepWindowOpen = false;
			}
		}
	}

	void Window::Maximize()
	{
		SDL_MaximizeWindow(window);
	}

	void Window::Minimize()
	{
		SDL_MinimizeWindow(window);
	}

	bool Window::KeepWindowOpen()
	{
		return keepWindowOpen;
	}

#ifdef _WIN32
	OpenFileDialog::OpenFileDialog() : filePath{ nullptr }, hr{ 0 }, dialog{ nullptr }, selectedItem{ nullptr }
	{
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&dialog));

			if (SUCCEEDED(hr))
			{
				hr = dialog->Show(nullptr);

				if (SUCCEEDED(hr))
				{
					hr = dialog->GetResult(&selectedItem);

					if (SUCCEEDED(hr))
					{
						selectedItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
					}
					else
						throw std::runtime_error("An error occured while getting results from file dialog.");
				}
				else
					throw std::runtime_error("No file was selected. Application will close.");
			}
		}
	}

	OpenFileDialog::~OpenFileDialog()
	{
		selectedItem->Release();
		dialog->Release();
		CoUninitialize();
	}

	std::wstring OpenFileDialog::GetFilePath()
	{
		if (!filePath)
			return std::wstring();
		else
			return filePath;
	}
#endif
}