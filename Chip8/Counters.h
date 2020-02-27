#pragma once
#include <cstdint>
#include <mutex>
#include <functional>

namespace Chip8
{
	class Counter
	{
		const uint8_t frequencyDivider{ 8 };
		std::mutex counterMutex;
		uint16_t frequencyCounter;
		uint8_t value;
		std::function<void(void)> callback;

	public:

		std::function<void(void)> CountingOn;
		std::function<void(void)> CountingFinished;

		Counter();
		~Counter();
		void SetValue(uint8_t value);
		uint8_t GetValue();
		void Decrement();
		void AttachCallback(std::function<void(void)> callback);

		Counter& operator=(const Counter&) = delete;
		Counter& operator=(Counter&&) = delete;
	};
}