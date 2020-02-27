#pragma once
#include <exception>
#include <stdexcept>
#include <cstdint>
#include <mutex>

namespace Chip8
{
	class KeyboardHandler
	{
		std::mutex keyboardHandlerMutex;
		uint8_t keyCode;
		bool isAnyKeyPressed;

	public:

		KeyboardHandler();
		~KeyboardHandler();

		void NoKeyPressed();
		void KeyPressed(uint8_t keyCode);
		bool IsAnyKeyPressed();
		uint8_t GetPressedKeyCode();
	};
}