#pragma once
#include <cstdint>
#include <mutex>

namespace Chip8
{
	class Counter
	{
		uint8_t value;

	public:

		Counter();
		void SetValue(uint8_t value);
		void Decrement();

		Counter& operator=(const Counter&) = delete;
		Counter& operator=(Counter&&) = delete;
	};
}