#include "Window.h"

namespace Chip8
{
	Window::Window(const std::string& title) : keepWindowOpen{ true }
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
				renderer = SDL_CreateRenderer(window, -1, NULL);

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

	void Window::PollEvents(KeyboardHandler& keyboardHandler)
	{
		SDL_Event e;
		keyboardHandler.NoKeyPressed();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				keepWindowOpen = false;
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

	void Window::Show()
	{
		SDL_ShowWindow(window);
	}

	void Window::Hide()
	{
		SDL_HideWindow(window);
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