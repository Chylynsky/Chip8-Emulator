#pragma once
#include <cstdint>
#include <array>
#include <future>
#include <SDL.h>
#include "GameWindow.h"

namespace Chip8
{
	// Class emulating GPU bahaviour in Chip8 and responsible for graphics generation to the specified window
	class GPU
	{
		// Original resolution is 64x32 pixels
		static constexpr uint8_t WIDTH{ 64 };
		static constexpr uint8_t HEIGHT{ 32 };
		// Display array
		std::array<std::array<uint8_t, HEIGHT>, WIDTH> display;
		GameWindow& window;
		// Ratio of current display width and original width in pixels
		int renderScale;
		
		// Display the current frame in the specified window
		void DisplayCurrent();

	public:

		GPU(GameWindow& window);
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