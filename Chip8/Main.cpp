#include <iostream>
#include "RAM.h"
#include "Registers.h"
#include "Timer.h"
#include "CPU.h"

using namespace std;
using namespace Chip8;

int main()
{
	CPU& cpu = CPU::GetInstance();
	cpu.Execute(6 << 12 | 3 << 8 | 6);
	cpu.Execute(7 << 12 | 3 << 8 | 6);
	
	return 0;
}