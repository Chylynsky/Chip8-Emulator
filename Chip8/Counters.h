#pragma once
#include <cstdint>
#include <mutex>

namespace Chip8
{
	class DelayCounter
	{
		static DelayCounter instance;
		uint8_t value;

		DelayCounter();

	public:

		static DelayCounter& GetInstance();
		void SetValue(uint8_t value);
		void Decrement();

		DelayCounter& operator=(const DelayCounter&) = delete;
		DelayCounter& operator=(DelayCounter&&) = delete;
	};

	class SoundCounter
	{
		static SoundCounter instance;
		uint8_t value;

		SoundCounter();

	public:

		static SoundCounter& GetInstance();
		void SetValue(uint8_t value);
		void Decrement();

		SoundCounter& operator=(const SoundCounter&) = delete;
		SoundCounter& operator=(SoundCounter&&) = delete;
	};
}