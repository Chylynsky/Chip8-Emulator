#include "Counters.h"

namespace Chip8
{
	Counter::Counter() : frequencyCounter{ 0 }, value{ 0 }, callback{ nullptr }, CountingOn{ nullptr }, CountingFinished{ nullptr }
	{
	}

	Counter::~Counter()
	{
	}

	void Counter::SetValue(uint8_t value)
	{
		std::lock_guard<std::mutex> counterGuard{ counterMutex };
		this->value = value;
	}

	uint8_t Counter::GetValue()
	{
		std::lock_guard<std::mutex> counterGuard{ counterMutex };
		return value;
	}

	void Counter::Decrement()
	{
		std::lock_guard<std::mutex> counterGuard{ counterMutex };

		if (value != 0)
		{	
			if (frequencyCounter < frequencyDivider - 1)
				frequencyCounter++;
			else
			{
				if (callback != nullptr)
					callback();

				if (CountingOn != nullptr)
					CountingOn();

				frequencyCounter = 0;
				value--;
			}
		}
		else
		{
			if (CountingFinished != nullptr)
				CountingFinished();
		}
	}
	
	void Counter::AttachCallback(std::function<void(void)> callback)
	{
		std::lock_guard<std::mutex> counterGuard{ counterMutex };
		this->callback = callback;
	}
}