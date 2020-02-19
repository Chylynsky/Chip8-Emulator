#include <iostream>
#include "Interpreter.h"

int main()
{
	using namespace std;
	using namespace Chip8;

	Interpreter interpreter{};
	interpreter.LoadROM("roms/test.ch8");
	interpreter.Start();

	cin.get();

	return 0;
}