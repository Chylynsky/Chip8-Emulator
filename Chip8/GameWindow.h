#pragma once
#include <cstdint>
#include <string>
#include <thread>
#include <chrono>
#include <queue>
#include <exception>
#include <stdexcept>
#include "SDL.h"
#include "KeyboardHandler.h"

#ifdef _WIN32
#include "Windows.h"
#include "shobjidl.h"
#endif

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

		static void ShowErrorBox(const std::string& message);

		void AddToRenderQueue(SDL_Rect texture);
		void Refresh();
		void PollEvents(KeyboardHandler& keyboardHandler);
		void Show();
		void Hide();
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