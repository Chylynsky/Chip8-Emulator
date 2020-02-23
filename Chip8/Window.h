#pragma once
#include <cstdint>
#include <string>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <exception>
#include <stdexcept>
#include "SDL.h"

#ifdef _WIN32
#include "Windows.h"
#include "shobjidl.h"
#endif

namespace Chip8
{
	class Window
	{
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::queue<SDL_Rect> textures;
		std::string title;
		bool keepWindowOpen;
		uint8_t pressedKeyCode;
		std::mutex windowMutex;

	public:

		int Width;
		int Height;

		Window(const std::string& title);
		~Window();

		static void ShowErrorBox(const std::string& message);

		uint8_t GetPressedKeyCode();
		void AddToRenderQueue(SDL_Rect texture);
		void Refresh();
		void PollEvents();
		void Maximize();
		void Minimize();
		bool KeepWindowOpen();
	};

#ifdef _WIN32
	class OpenFileDialog
	{
		PWSTR filePath;
		HRESULT hr;
		IFileOpenDialog* dialog;
		IShellItem* selectedItem;

	public:

		OpenFileDialog();
		~OpenFileDialog();
		std::wstring GetFilePath();
	};
#endif
}