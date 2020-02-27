#include "AudioFile.h"

namespace Chip8
{
	AudioFile::AudioFile(const std::string& loadPath) : length{ 0 }, buffer{ nullptr }, deviceId{ 0 }, isPlaying{ false }
	{
		if (!SDL_LoadWAV(loadPath.c_str(), &audioSpec, &buffer, &length))
			throw std::runtime_error("File " + loadPath + " could not be loaded.");

		SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(nullptr, false, &audioSpec, nullptr, false);

		if (!deviceId)
			throw std::runtime_error("Could not open audio device.");

		SDL_QueueAudio(deviceId, buffer, length);
		SDL_PauseAudioDevice(deviceId, 0);
	}

	AudioFile::~AudioFile()
	{
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(buffer);
	}

	bool AudioFile::IsPlaying()
	{
		return isPlaying;
	}

	void AudioFile::Play()
	{
		SDL_QueueAudio(deviceId, buffer, length);
		isPlaying = true;
	}

	void AudioFile::Pause()
	{
		SDL_PauseAudioDevice(deviceId, 0);
		isPlaying = false;
	}

	void AudioFile::AudioCallback(void* data, Uint8* stream, int length)
	{
		//SDL_MixAudio(stream, audio_pos, length, SDL_MIX_MAXVOLUME);
	}
}