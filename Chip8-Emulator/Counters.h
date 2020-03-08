#pragma once
#include <cstdint>
#include <mutex>
#include <functional>

namespace Chip8
{
	// Class specifying counters behaviour in Chip8
	// Counter object has to be controlled by the external timer which periodically calls its Decrement method
	class Counter
	{
		// Value by which the main clock frequency is to be divided
		const int frequencyDivider;
		// Main clock tick counter
		uint16_t frequencyCounter;
		// Current counter value
		uint8_t value;

	public:

		// Callbacks
		// Function gets called every time the counters value decreases
		std::function<void(void)> CountingOn;
		// Function gets called every time the counters value reaches 0
		std::function<void(void)> CountingFinished;

		explicit Counter(int frequencyDivider);
		~Counter();

		// Set the counters value
		void SetValue(uint8_t value);
		// Get the counters value
		uint8_t GetValue();
		// Decrease the counters value, this method needs to be called periodically by the main clock
		void Decrement();

		Counter& operator=(const Counter&) = delete;
		Counter& operator=(Counter&&) = delete;
	};
}