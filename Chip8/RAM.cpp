#include "RAM.h"

namespace Chip8
{
	const std::array<uint8_t, 80> RAM::FONTSET
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	RAM::RAM() : memory{}
	{
		// Fill RAM memory with font data
		std::copy(FONTSET.begin(), FONTSET.end(), memory.begin() + FONTSET_ADDRESS);
	}

	RAM::~RAM()
	{
	}

	void RAM::LoadROM(const std::string& loadPath)
	{
		std::lock_guard<std::mutex> ramGuard{ ramMutex };
		ROMLoader loader{ loadPath };
		loader.Load(memory.begin() + PROGRAM_MEMORY_ADDRESS, memory.end());
	}

	void RAM::LoadROM(const std::wstring& loadPath)
	{
		std::lock_guard<std::mutex> ramGuard{ ramMutex };
		ROMLoader loader{ loadPath };
		loader.Load(memory.begin() + PROGRAM_MEMORY_ADDRESS, memory.end());
	}

	void RAM::ClearProgramMemory()
	{
		std::lock_guard<std::mutex> ramGuard{ ramMutex };
		auto first = memory.begin() + PROGRAM_MEMORY_ADDRESS;
		while (first != memory.end())
			*first = 0;
	}

	uint8_t& RAM::operator[](uint16_t address)
	{
		return memory[address];
	}

}