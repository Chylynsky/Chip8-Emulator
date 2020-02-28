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
		SDL_PauseAudioDevice(deviceId, false);
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
		if (isPlaying)
			return;

		SDL_QueueAudio(deviceId, buffer, length);
		//SDL_PauseAudioDevice(deviceId, false);
		isPlaying = true;
	}

	void AudioFile::Pause()
	{
		if (!isPlaying)
			return;

		SDL_PauseAudioDevice(deviceId, true);
		isPlaying = false;
	}
}