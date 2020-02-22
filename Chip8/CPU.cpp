#include "CPU.h"

namespace Chip8
{
	CPU::CPU(GPU& gpu, RAM& ram, Counter& delayCounter, Counter& soundCounter) : gpu{ gpu }, ram { ram }, delayCounter{ delayCounter }, soundCounter{ soundCounter },
		generalPurposeRegisters{}, memoryAddressRegister{ 0 }, programCounter{ 0x200 }, Random{ std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max() }
	{
	}

	CPU::~CPU()
	{
	}

	// Comments in CPU::Execute method taken from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
	void CPU::ExecuteCycle()
	{
		static uint16_t instruction = 0;

		std::lock_guard<std::mutex> cpuGuard{ cpuMutex };
		std::lock_guard<std::mutex> ramGuard{ ram.ramMutex };
		
		switch (instruction = ram[programCounter] << 8 | ram[programCounter + 1]; instruction >> 0xC)
		{
		case 0x0:
			switch (instruction & 0xFF)
			{
			case 0xE0: // 00E0 - Clear the display.
				gpu.DisplayClear();
				programCounter += 2;
				break;
			case 0xEE: // 00EE - The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
				programCounter = stack.top();
				stack.pop();
				programCounter += 2;
				break;
			default: 
				std::stringstream sstr;
				sstr << "Instruction 0x" << std::hex << instruction << " not recognized at location 0x" << programCounter << " (" << std::dec << programCounter << ").";
#ifdef _DEBUG
				std::cout << sstr.str() << std::endl;
#endif
				throw std::runtime_error(sstr.str());
				break;
			}
			break;
		case 0x1: // 1nnn - The interpreter sets the program counter to nnn.
			programCounter = instruction & 0xFFF; 
			break;
		case 0x2: // 2nnn - The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
			stack.push(programCounter);
			programCounter = instruction & 0xFFF;
			break;
		case 0x3: // 3xkk - The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] == (instruction & 0xFF)) ? 2 : 0;
			programCounter += 2;
			break;
		case 0x4: // 4xkk - The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] != (instruction & 0xFF)) ? 2 : 0;
			programCounter += 2;
			break;
		case 0x5: // 5xy0 - The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] == generalPurposeRegisters[instruction >> 0x4 & 0xF]) ? 2 : 0;
			programCounter += 2;
			break;
		case 0x6: // 6xkk - The interpreter puts the value kk into register Vx.
			generalPurposeRegisters[instruction >> 0x8 & 0xF] = instruction & 0xFF;
			programCounter += 2;
			break;
		case 0x7: // 7xkk - Adds the value kk to the value of register Vx, then stores the result in Vx.
			generalPurposeRegisters[instruction >> 0x8 & 0xF] += (instruction & 0xFF);
			programCounter += 2;
			break;
		case 0x8:
			switch (instruction & 0xF)
			{
			case 0x0: // 8xy0 - Stores the value of register Vy in register Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] =  generalPurposeRegisters[instruction >> 0x4 & 0xF];
				programCounter += 2;
				break;
			case 0x1: // 8xy1 - Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] |= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				programCounter += 2;
				break;
			case 0x2: // 8xy2 - Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] &= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				programCounter += 2;
				break;
			case 0x3: // 8xy3 - 8xy3 - Performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx.
				generalPurposeRegisters[instruction >> 0x8 & 0xF] ^= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				programCounter += 2;
				break;
			case 0x4: // 8xy4 - The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0.
				generalPurposeRegisters[0xF] = (generalPurposeRegisters[instruction >> 0x8 & 0xF] + generalPurposeRegisters[instruction >> 0x4 & 0xF] > 0xFF) ? 1 : 0;
				generalPurposeRegisters[instruction >> 0x8 & 0xF] = generalPurposeRegisters[instruction >> 0x8 & 0xF] + generalPurposeRegisters[instruction >> 0x4 & 0xF] > 0xFF;
				programCounter += 2;
				break;
			case 0x5: // 8xy5 - If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
				generalPurposeRegisters[0xF] = (generalPurposeRegisters[instruction >> 0x8 & 0xF] > generalPurposeRegisters[instruction >> 0x4 & 0xF]);
				generalPurposeRegisters[instruction >> 0x8 & 0xF] -= generalPurposeRegisters[instruction >> 0x4 & 0xF];
				programCounter += 2;
				break;
			case 0x6: // 8xy6 - If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
				generalPurposeRegisters[0xF] = generalPurposeRegisters[instruction >> 0x8 & 0xF] & 0x1;
				generalPurposeRegisters[instruction >> 0x8 & 0xF] /= 2;
				programCounter += 2;
				break;
			case 0x7: // 8xy7 - If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
				generalPurposeRegisters[0xF] = (generalPurposeRegisters[instruction >> 0x8 & 0xF] < generalPurposeRegisters[instruction >> 0x4 & 0xF]);
				generalPurposeRegisters[instruction >> 0x4 & 0xF] -= generalPurposeRegisters[instruction >> 0x8 & 0xF];
				programCounter += 2;
				break;
			case 0xE: // 8xyE - If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
				generalPurposeRegisters[0xF] = generalPurposeRegisters[instruction >> 0x8 & 0xF] & 0x80;
				generalPurposeRegisters[instruction >> 0x8 & 0xF] *= 2;
				programCounter += 2;
				break;
			default:
				std::stringstream sstr;
				sstr << "Instruction 0x" << std::hex << instruction << " not recognized at location 0x" << programCounter << " (" << std::dec << programCounter << ").";
#ifdef _DEBUG
				std::cout << sstr.str() << std::endl;
#endif
				throw std::runtime_error(sstr.str());
				break;
			}
			break;
		case 0x9: // 9xy0 - The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
			programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] != generalPurposeRegisters[instruction >> 0x4 & 0xF]) ? 2 : 0;
			programCounter += 2;
			break;
		case 0xA: // Annn - The value of register I is set to nnn.
			memoryAddressRegister = instruction & 0xFFF;
			programCounter += 2;
			break;
		case 0xB: // Bnnn - The program counter is set to nnn plus the value of V0.
			programCounter = generalPurposeRegisters[0x0] + (instruction & 0xFFF);
			break;
		case 0xC: // Cxkk - The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx.
			generalPurposeRegisters[instruction >> 8 & 0xF] = (instruction & 0xFF) & static_cast<uint8_t>(Random(randomEngine));
			programCounter += 2;
			break;
		case 0xD: // Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
			generalPurposeRegisters[0xF] = gpu.DisplaySprite
			(
				generalPurposeRegisters[instruction >> 8 & 0xF], // x
				generalPurposeRegisters[instruction >> 4 & 0xF],  // y
				&ram[memoryAddressRegister], // pointer to the first byte
				&ram[memoryAddressRegister + (instruction & 0xF)] // pointer to the one past last byte
			);
			programCounter += 2;
			break;
		case 0xE:
			switch (instruction & 0xFF)
			{
			case 0x9E: // Ex9E - Skip next instruction if key with the value of Vx is pressed.
			{
				std::cout << "Keyboard input required: ";
				uint8_t key = 0;
				std::cin >> key;
				std::cout << std::endl;
				programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] == key) ? 2 : 0;
				programCounter += 2;
			}
				break;
			case 0xA1: // ExA1 - Skip next instruction if key with the value of Vx is not pressed.
			{
				std::cout << "Keyboard input required: ";
				uint8_t key = 0;
				std::cin >> key;
				std::cout << std::endl;
				programCounter += (generalPurposeRegisters[instruction >> 0x8 & 0xF] != key) ? 2 : 0;
				programCounter += 2;
			}
				break;
			default:
				std::stringstream sstr;
				sstr << "Instruction 0x" << std::hex << instruction << " not recognized at location 0x" << programCounter << " (" << std::dec << programCounter << ").";
#ifdef _DEBUG
				std::cout << sstr.str() << std::endl;
#endif
				throw std::runtime_error(sstr.str());
				break;
			}
			break;
		case 0xF:
			switch (instruction & 0xFF)
			{
			case 0x07: // Fx07 - The value of DT is placed into Vx.
				generalPurposeRegisters[instruction >> 8 & 0xF] = delayCounter.GetValue();
				programCounter += 2;
				break;
			case 0x0A: // Fx0A - Wait for a key press, store the value of the key in Vx.
			{
				std::cout << "Keyboard input required: ";
				uint8_t key = 0;
				std::cin >> key;
				std::cout << std::endl;
				generalPurposeRegisters[instruction >> 8 & 0xF] = key;
			}
				programCounter += 2;
				break;
			case 0x15: // Fx15 - DT is set equal to the value of Vx.
				delayCounter.SetValue(generalPurposeRegisters[instruction >> 8 & 0xF]);
				programCounter += 2;
				break;
			case 0x18:
				soundCounter.SetValue(generalPurposeRegisters[instruction >> 8 & 0xF]);
				programCounter += 2;
				break;
			case 0x1E: // Fx1E - The values of I and Vx are added, and the results are stored in I.
				memoryAddressRegister += generalPurposeRegisters[instruction >> 0x8 & 0xF];
				programCounter += 2;
				break;
			case 0x29: // Fx29 - The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
				memoryAddressRegister = 4 * (instruction >> 8 & 0xF);
				programCounter += 2;
				break;
			case 0x33: // Fx33 - The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
				ram[memoryAddressRegister] = generalPurposeRegisters[instruction >> 8 & 0xF] / 100;
				ram[memoryAddressRegister + 1] = (generalPurposeRegisters[instruction >> 8 & 0xF] / 10) % 10;
				ram[memoryAddressRegister + 2] = generalPurposeRegisters[instruction >> 8 & 0xF] % 10;
				programCounter += 2;
				break;
			case 0x55: // Fx55 - The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
				for (uint8_t i = 0; i < (instruction >> 0x8 & 0xF); i++)
					ram[memoryAddressRegister + i] = generalPurposeRegisters[i];
				programCounter += 2;
				break;
			case 0x65: // Fx65 - The interpreter reads values from memory starting at location I into registers V0 through Vx.
				for (uint8_t i = 0; i < (instruction >> 0x8 & 0xF); i++)
					generalPurposeRegisters[i] = ram[memoryAddressRegister + i];
				programCounter += 2;
				break;
			default:
				std::stringstream sstr;
				sstr << "Instruction 0x" << std::hex << instruction << " not recognized at location 0x" << programCounter << " (" << std::dec << programCounter << ").";
#ifdef _DEBUG
				std::cout << sstr.str() << std::endl;
#endif
				throw std::runtime_error(sstr.str());
				break;
			}
			break;
		default:
			std::stringstream sstr;
			sstr << "Instruction 0x" << std::hex << instruction << " not recognized at location 0x" << programCounter << " (" << std::dec << programCounter << ").";
#ifdef _DEBUG
			std::cout << sstr.str() << std::endl;
#endif
			throw std::runtime_error(sstr.str());
			break;
		}
	}

	void CPU::Reset()
	{
		std::lock_guard<std::mutex> cpuGuard{ cpuMutex };
		std::stack<uint16_t>().swap(stack);
		memoryAddressRegister = 0;
		programCounter = 0x200;
	}
}