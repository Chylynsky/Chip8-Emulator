#include "GPU.h"

namespace Chip8
{
	void GPU::DisplayCurrent()
	{
		for (int i = 0; i < display.size(); i++)
		{
			for (int j = 0; j < display[i].size(); j++)
			{
				if (display[i][j] == 1)
				{
					SDL_Rect rect{ i * renderScale, j * renderScale, renderScale, renderScale };
					window.AddToRenderQueue(rect);
				}
			}
		}

		window.Refresh();
	}

	GPU::GPU(Window& window) : display{}, window{ window }, renderScale{ window.Width / 64 }
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
			for (size_t shift = 0; shift < 8; shift++)
			{
				tmp = display[xPos][y];
				display[xPos][y] ^= (*first >> (8 - shift - 1) & 0xF);

				// Result is 1 if any pixel turns from 1 to 0
				if (tmp == 1 && display[xPos][y] == 0)
					result = 1;

				xPos = (xPos < display.size() - 1) ? xPos + 1 : 0;
			}

			first++;
			y = (y < display[0].size() - 1) ? y + 1 : 0;
		}

		DisplayCurrent();
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