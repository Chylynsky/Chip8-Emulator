#include "TonePlayer.h"

namespace Chip8
{
	void TonePlayer::AudioCallback(void* data, uint8_t* stream, int length)
	{
		TonePlayer* tonePlayer = reinterpret_cast<TonePlayer*>(data);

		for (uint16_t i = 0; i < length; i++)
			*(stream + i) = tonePlayer->samples[i];
	}

	TonePlayer::TonePlayer(float frequency) : frequency { frequency }
	{
		float period = 1.0f / frequency;
		float samplingPeriod = 1.0f / SamplingFrequency;
		samples.resize(static_cast<uint8_t>(std::round(period / samplingPeriod)));

		// Create samples of distorted sine wave
		for (uint16_t t = 0; t < samples.size(); t++)
			samples[t] = static_cast<uint8_t>(std::round(128.0f * std::sin(2.0f * M_PI * frequency / SamplingFrequency * static_cast<float>(t)) + 127.0f));

		audioSpec.channels = 1;
		audioSpec.freq = static_cast<int>(SamplingFrequency);
		audioSpec.format = AUDIO_U8;
		audioSpec.samples = static_cast<uint16_t>(samples.size());
		audioSpec.userdata = this;
		audioSpec.callback = AudioCallback;

		SDL_OpenAudio(&audioSpec, nullptr);
		SDL_PauseAudio(true);
	}

	TonePlayer::~TonePlayer()
	{
		SDL_CloseAudio();
	}

	void TonePlayer::Play()
	{
		SDL_PauseAudio(false);
	}

	void TonePlayer::Stop()
	{
		SDL_PauseAudio(true);
	}
}