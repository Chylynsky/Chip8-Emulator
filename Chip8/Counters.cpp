#include "Counters.h"

namespace Chip8
{
	Counter::Counter() : value{ 0 }
	{
	}

	void Counter::SetValue(uint8_t value)
	{
		this->value = value;
	}

	void Counter::Decrement()
	{
		value--;
	}
}