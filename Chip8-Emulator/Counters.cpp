#include "Counters.h"

namespace Chip8
{
	Counter::Counter(int frequencyDivider) : frequencyDivider{ frequencyDivider }, frequencyCounter { 0 }, value{ 0 }, CountingOn{ nullptr }, CountingFinished{ nullptr }
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
		{	
			if (frequencyCounter < frequencyDivider - 1)
				frequencyCounter++;
			else
			{
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
}