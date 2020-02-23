#pragma once
#include <cstdint>
#include <mutex>

namespace Chip8
{
	class Counter
	{
		std::mutex counterMutex;
		uint8_t value;

	public:

		Counter();
		~Counter();
		void SetValue(uint8_t value);
		uint8_t GetValue();
		void Decrement();

		Counter& operator=(const Counter&) = delete;
		Counter& operator=(Counter&&) = delete;
	};
}