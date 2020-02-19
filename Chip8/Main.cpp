#include <iostream>
#include "Interpreter.h"

int main()
{
	using namespace std;
	using namespace Chip8;

	Interpreter& interpreter{ Interpreter::GetInstance() };
	interpreter.LoadROM("roms/test.ch8");
	interpreter.Start();

	cin.get();

	//interpreter.Stop();

	return 0;
}