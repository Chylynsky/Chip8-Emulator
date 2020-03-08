#pragma once
#include <cstdint>
#include <string>
#include <mutex>
#include <array>
#include <exception>
#include <stdexcept>
#include "ROMLoader.h"

namespace Chip8
{
	// RAM struct handles Chip8 RAM emulation
	struct RAM
	{
		static constexpr uint16_t MEMORY_CAPACITY{ 4096 };
		static constexpr uint16_t FONTSET_ADDRESS{ 0x00 };
		static constexpr uint16_t PROGRAM_MEMORY_ADDRESS{ 0x200 };
		static const std::array<uint8_t, 80> FONTSET;

		RAM();
		~RAM();
		void LoadROM(const std::string& loadPath);
		void LoadROM(const std::wstring& loadPath);
		void ClearProgramMemory();

		RAM& operator=(const RAM&) = delete;
		RAM& operator=(RAM&&) = delete;
		uint8_t& operator[](uint16_t address);

	private:

		std::mutex ramMutex;
		std::array<uint8_t, MEMORY_CAPACITY> memory;
	};
}