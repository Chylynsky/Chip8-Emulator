#pragma once
#include <cstdint>
#include <string>
#include "ROMLoader.h"

namespace Chip8
{
	class RAM
	{
		static constexpr uint16_t MEMORY_CAPACITY{ 4096 };

		static RAM instance;

		uint8_t memory[MEMORY_CAPACITY];

	public:

		static RAM& GetInstance();
		void LoadFile(const std::string& loadPath);

		RAM& operator=(const RAM&) = delete;
		RAM& operator=(RAM&&) = delete;
		uint8_t& operator[](uint16_t address);
	};
}