#pragma once
#include <cstdint>
#include <string>
#include <mutex>
#include <vector>
#include <exception>
#include <stdexcept>
#include "ROMLoader.h"

#ifdef _DEBUG
#include <iostream>
#endif


namespace Chip8
{
	class RAM
	{
		static constexpr uint16_t MEMORY_CAPACITY{ 4096 };

		std::vector<uint8_t> memory;

	public:

		std::mutex ramMutex;

		RAM();
		void LoadROM(const std::string& loadPath);

		RAM& operator=(const RAM&) = delete;
		RAM& operator=(RAM&&) = delete;
		uint8_t& operator[](uint16_t address);
	};
}