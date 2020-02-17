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

	// Comments in CPU::Execute method taken from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
	void CPU::Execute(uint16_t instruction)
	{
		switch (instruction >> 0xC)
		{
		case 0x0:
			switch (instruction & 0xFF)
			{
			case 0xE0:
				break;
			case 0xEE: // 00EE - The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
				programCounter = stack.Top();
				stack.Pop();
				break;
			default: break;
			}
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
			switch (instruction & 0xF)
			{
			case 0x0: // 8xy0 - Stores the value of register Vy in register Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] =  generalPurposeRegisters[instruction >> 0x4 & 0xF];
				break;
			case 0x1: // 8xy1 - Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] |= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				break;
			case 0x2: // 8xy2 - Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] &= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				break;
			case 0x3: // 8xy3 - 8xy3 - Performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] ^= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				break;
			case 0x4: // 8xy4 - The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0.
				uint16_t tmp = generalPurposeRegisters[instruction >> 0x8 & 0xF] + generalPurposeRegisters[instruction >> 0x4 & 0xF];
				generalPurposeRegisters[0xF] = (tmp > 0xFF) ? 1 : 0;
				generalPurposeRegisters[instruction >> 0x8 & 0xF] = tmp;
				break;
			case 0x5: // 8xy5 - If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
				generalPurposeRegisters[0xF] = (generalPurposeRegisters[instruction >> 0x8 & 0xF] > generalPurposeRegisters[instruction >> 0x4 & 0xF]);
				generalPurposeRegisters[instruction >> 0x8 & 0xF] -= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				break;
			case 0x6: // 8xy6 - If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
				generalPurposeRegisters[0xF] = generalPurposeRegisters[instruction >> 0x8 & 0xF] & 0x1;
				generalPurposeRegisters[instruction >> 0x8 & 0xF] /= 2;
				break;
			case 0x7: // 8xy7 - If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
				generalPurposeRegisters[0xF] = (generalPurposeRegisters[instruction >> 0x8 & 0xF] < generalPurposeRegisters[instruction >> 0x4 & 0xF]);
				generalPurposeRegisters[instruction >> 0x4 & 0xF] -= generalPurposeRegisters[instruction >> 0x8 & 0xF];
				break;
			case 0xE: // 8xyE - If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
				generalPurposeRegisters[0xF] = generalPurposeRegisters[instruction >> 0x8 & 0xF] & 0x80;
				generalPurposeRegisters[instruction >> 0x8 & 0xF] *= 2;
				break;
			default: break;
			}
			break;
		case 0x9: // 9xy0 - The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] != generalPurposeRegisters[instruction >> 0x4 & 0xF]) ? 2 : 0;
			break;
		case 0xA: // Annn - The value of register I is set to nnn.
			memoryAddressRegister = instruction & 0xFFF;
			break;
		case 0xB: // Bnnn - The program counter is set to nnn plus the value of V0.
			programCounter = generalPurposeRegisters[0x0] + instruction & 0xFFF;
			break;
		case 0xC:
			break;
		case 0xD:
			break;
		case 0xE:
			break;
		case 0xF:
			switch (instruction & 0xFF)
			{
			case 0x07:
				break;
			case 0x0A:
				break;
			case 0x15:
				break;
			case 0x18:
				break;
			case 0x1E: // Fx1E - The values of I and Vx are added, and the results are stored in I.
				memoryAddressRegister += generalPurposeRegisters[instruction >> 0x8 & 0xF];
				break;
			}
			break;
		default:
			break;
		}
	}
}