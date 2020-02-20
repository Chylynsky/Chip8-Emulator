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
		this->value = value;
	}

	uint8_t Counter::GetValue()
	{
		return value;
	}

	void Counter::Decrement()
	{
		if (value != 0)
			value--;
		else
			return;
	}
}