#pragma once
#include <cstdint>
#include <thread>
#include <atomic>
#include <cmath>
#include <vector>
#include <array>
#include <limits>
#include "SDL.h"
#include "SDL_audio.h"

namespace Chip8
{
	// Class responsible for generating 8-bit tones
	class TonePlayer
	{
		static constexpr float SamplingFrequency{ 44100.0f };

		SDL_AudioSpec audioSpec;
		std::vector<uint8_t> samples;
		float frequency;

		static void AudioCallback(void*, uint8_t*, int);

	public:

		explicit TonePlayer(float frequency = 440.0f);
		~TonePlayer();

		// Start playback
		void Play();
		// Stop playback
		void Stop();
	};
}