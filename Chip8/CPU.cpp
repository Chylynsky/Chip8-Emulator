#include "CPU.h"

namespace Chip8
{
	CPU CPU::instance{};

	CPU::CPU() : generalPurposeRegisters{ GeneralPurposeRegisters::GetInstance() }, ram{ RAM::GetInstance() }, stack{ Stack::GetInstance() }, memoryAddressRegister{ 0 }, programCounter{ 0 }
	{

	}

	CPU& CPU::GetInstance()
	{
		return instance;
	}

	// Comments in Execute method taken from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
	void CPU::Execute(uint16_t instruction)
	{
		switch (instruction >> 0xC)
		{
		case 0x0:
			break;
		case 0x1: // 1nnn - The interpreter sets the program counter to nnn.
			programCounter = instruction & 0xFFF;
			break;
		case 0x2:
			break;
		case 0x3: // 3xkk - The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] == (instruction & 0xFF)) ? 2 : 0;
			break;
		case 0x4: // 4xkk - The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] != (instruction & 0xFF)) ? 2 : 0;
			break;
		case 0x5: // 5xy0 - The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] == generalPurposeRegisters[instruction >> 0x4 & 0xF]) ? 2 : 0;
			break;
		case 0x6: // 6xkk - The interpreter puts the value kk into register Vx.
			generalPurposeRegisters[(instruction >> 0x8) & 0xF] = instruction & 0xFF;
			break;
		case 0x7: // 7xkk - Adds the value kk to the value of register Vx, then stores the result in Vx.
			generalPurposeRegisters[(instruction >> 0x8) & 0xF] += instruction & 0xFF;
			break;
		case 0x8:
			break;
		case 0x9:
			break;
		case 0xA:
			break;
		case 0xB:
			break;
		case 0xC:
			break;
		case 0xD:
			break;
		case 0xE:
			break;
		case 0xF:
			break;
		default:
			break;
		}
	}
}