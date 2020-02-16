#pragma once
#include <cstdint>
#include "Memory.h"
#include "Registers.h"
#include "Timers.h"

namespace Chip8
{
	class ALU
	{
		

	public:

		void Execute(uint16_t instruction);

	};
}