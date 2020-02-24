#include "GPU.h"

namespace Chip8
{
	void GPU::DisplayCurrent()
	{
		for (int i = 0; i < display.size(); i++)
		{
			for (int j = 0; j < display[i].size(); j++)
			{
				if (display[i][j] > 0)
				{
					SDL_Rect rect{ i * renderScale, j * renderScale, renderScale, renderScale };
					window.AddToRenderQueue(rect);
				}
			}
		}

		window.Refresh();
	}

	GPU::GPU(Window& window) : display{}, window{ window }, renderScale{ window.Width / WIDTH }
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
			uint8_t xPos = x;

			if (y >= display[0].size())
				y %= display[0].size();

			for (size_t shift = 0; shift < 8; shift++)
			{
				if (xPos >= display.size())
					xPos %= display.size();

				tmp = display[xPos][y];
				display[xPos][y] ^= (*first >> (8 - shift - 1) & 0x1);

				// Result is 1 if any pixel turns from 1 to 0
				if (tmp == 1 && display[xPos][y] == 0)
					result = 1;

				xPos++;
			}

			first++;
			y++;
		}
		std::async(std::bind(&GPU::DisplayCurrent, this));
		return result;
	}

	void GPU::DisplayClear()
	{
		for (size_t i = 0; i < display.size(); i++)
		{
			for (size_t j = 0; j < display[i].size(); j++)
			{
				display[i][j] = 0;
			}
		}

		window.Refresh();
	}
}