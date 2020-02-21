#include "GPU.h"

namespace Chip8
{
	GPU::GPU(Window& window) : display{}, window { window }
	{
	}

	GPU::~GPU()
	{
	}

	uint8_t GPU::DisplaySprite(uint8_t x, uint8_t y, uint8_t* first, const uint8_t* last)
	{
		uint8_t tmp = 0, result = 0;

		while (first != last)
		{
			for (size_t shift = 0; shift < sizeof(uint8_t); shift++)
			{
				tmp = display[x + shift][y];
				display[x + shift][y] ^= (*first >> (sizeof(uint8_t) - shift));

				// Result is 1 if any pixel turns from 1 to 0
				if (tmp == 1 && display[x + shift][y] == 0)
					result = 1;
			}

			first++;
			y++;
		}

		return result;
	}

	void GPU::DisplayClear()
	{
		for (std::array<uint8_t, 32> row : display)
		{
			for (uint8_t elem : row)
				elem = 0;
		}
	}
}