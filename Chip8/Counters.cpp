#include "Counters.h"

namespace Chip8
{
	DelayCounter DelayCounter::instance{};

	DelayCounter::DelayCounter() : value{ 0 }
	{
	}

	DelayCounter& Chip8::DelayCounter::GetInstance()
	{
		return instance;
	}

	void DelayCounter::SetValue(uint8_t value)
	{
		this->value = value;
	}

	void DelayCounter::Decrement()
	{
		value--;
	}

	SoundCounter SoundCounter::instance{};
	
	SoundCounter::SoundCounter() : value{ 0 }
	{
	}

	SoundCounter& SoundCounter::GetInstance()
	{
		return instance;
	}

	void SoundCounter::SetValue(uint8_t value)
	{
		this->value = value;
	}

	void SoundCounter::Decrement()
	{
		value--;
	}
}