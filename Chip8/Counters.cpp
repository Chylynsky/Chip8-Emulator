#include "Counters.h"

namespace Chip8
{
	Counter::Counter() : frequencyCounter{ 0 }, value{ 0 }, callback{ nullptr }
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
			if (callback != nullptr)
				callback();

			if (frequencyCounter < frequencyDivider - 1)
			{
				frequencyCounter++;
				return;
			}
			else
			{
				frequencyCounter = 0;
				value--;
			}
		}
		else
		{
			return;
		}
	}

	void Counter::AttachCallback(std::function<void(void)> callback)
	{
		this->callback = callback;
	}
}