#pragma once
#include <cstdint>
#include <string>
#include <mutex>
#include <array>
#include <exception>
#include <stdexcept>
#include <array>
#include "ROMLoader.h"

#ifdef _DEBUG
#include <iostream>
#endif


namespace Chip8
{
	class RAM
	{
		static constexpr uint16_t MEMORY_CAPACITY{ 4096 };
		static constexpr uint16_t FONTSET_ADDRESS{ 0x00 };
		static const std::array<uint8_t, 80> FONTSET;

		std::array<uint8_t, MEMORY_CAPACITY> memory;

	public:

		std::mutex ramMutex;

		RAM();
		~RAM();
		void LoadROM(const std::string& loadPath);
		void LoadROM(const std::wstring& loadPath);

		RAM& operator=(const RAM&) = delete;
		RAM& operator=(RAM&&) = delete;
		uint8_t& operator[](uint16_t address);
	};
}