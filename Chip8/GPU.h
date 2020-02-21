#pragma once
#include <cstdint>
#include <array>
#include "Window.h"

namespace Chip8
{
	class GPU
	{
		// Original resolution is 64x32 pixels
		std::array<std::array<uint8_t, 32>, 64> display;
		Window& window;

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