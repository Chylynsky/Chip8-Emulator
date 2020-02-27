#pragma once
#include <cstdint>
#include <string>
#include <exception>
#include <stdexcept>
#include "SDL.h"

namespace Chip8
{
	class AudioFile
	{
		uint32_t length;
		uint8_t* buffer;
		SDL_AudioSpec audioSpec;
		SDL_AudioDeviceID deviceId;
		bool isPlaying;

	public:

		AudioFile(const std::string& loadPath);
		~AudioFile();

		bool IsPlaying();
		void Play();
		void Pause();

		static void AudioCallback(void* data, Uint8* stream, int length);
	};
}