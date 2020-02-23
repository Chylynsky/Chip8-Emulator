#pragma once
#include <cstdint>
#include <array>
#include <future>
#include <SDL.h>
#include "Window.h"

namespace Chip8
{
	class GPU
	{
		// Original resolution is 64x32 pixels
		static constexpr uint8_t WIDTH{ 64 };
		static constexpr uint8_t HEIGHT{ 32 };
		std::array<std::array<uint8_t, HEIGHT>, WIDTH> display;
		Window& window;
		int renderScale;
		
		void DisplayCurrent();

	public:

		GPU(Window& window);
		~GPU();

		// (x, y) - desired position of the sprite
		// [first, last) - pointers to bytes containing the sprite (last refers to the byte past the last byte)
		// Returns 1 if pixel collision was detected, 0 otherwise
		uint8_t DisplaySprite(uint8_t x, uint8_t y, uint8_t* first, const uint8_t* last);
		void DisplayClear();

		GPU& operator=(const GPU&) = delete;
		GPU& operator=(GPU&&) = delete;
	};
}