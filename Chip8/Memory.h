#pragma once
#include <cstdint>

namespace Chip8
{
	class Memory
	{
		static constexpr uint16_t MEMORY_CAPACITY{ 4096 };
		static Memory instance;

		uint8_t memory[MEMORY_CAPACITY];

	public:

		static Memory& GetInstance();

		Memory& operator=(const Memory&) = delete;
		Memory& operator=(Memory&&) = delete;
		uint8_t& operator[](uint16_t registerNumber);
	};
}