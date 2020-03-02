#pragma once
#include <thread>
#include <atomic>

namespace Chip8
{
	class TonePlayer
	{
		std::atomic<bool> isPlaying;

	public:

		explicit TonePlayer(float frequency = 440.0f, float loudness = 1.0f);
		~TonePlayer();
	};
}