#include "Counters.h"

namespace Chip8
{
	Counter::Counter() : value{ 0 }
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
			value--;
		else
			return;
	}
}