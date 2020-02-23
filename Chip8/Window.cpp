#include "Window.h"

namespace Chip8
{
	Window::Window(const std::string& title) : title{ title }, keepWindowOpen{ true }, pressedKeyCode{ 0x0 }
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

	uint8_t Window::GetPressedKeyCode()
	{
		std::lock_guard<std::mutex> windowMutexGuard{ windowMutex };
		return pressedKeyCode;
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

		std::lock_guard<std::mutex> windowMutexGuard{ windowMutex };
		pressedKeyCode = 0x0;

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
					pressedKeyCode = 0x0;
					break;
				case SDLK_1:
					pressedKeyCode = 0x1;
					break;
				case SDLK_2:
					pressedKeyCode = 0x2;
					break;
				case SDLK_3:
					pressedKeyCode = 0x3;
					break;
				case SDLK_4:
					pressedKeyCode = 0x4;
					break;
				case SDLK_5:
					pressedKeyCode = 0x5;
					break;
				case SDLK_6:
					pressedKeyCode = 0x6;
					break;
				case SDLK_7:
					pressedKeyCode = 0x7;
					break;
				case SDLK_8:
					pressedKeyCode = 0x8;
					break;
				case SDLK_9:
					pressedKeyCode = 0x9;
					break;
				case SDLK_a:
					pressedKeyCode = 0xA;
					break;
				case SDLK_b:
					pressedKeyCode = 0xB;
					break;
				case SDLK_c:
					pressedKeyCode = 0xC;
					break;
				case SDLK_d:
					pressedKeyCode = 0xD;
					break;
				case SDLK_e:
					pressedKeyCode = 0xE;
					break;
				case SDLK_f:
					pressedKeyCode = 0xF;
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