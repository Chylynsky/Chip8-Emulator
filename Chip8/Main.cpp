#include <iostream>
#include "SDL.h"
#include "Interpreter.h"

int main(int argc, char* argv[])
{
	using namespace std;
	using namespace Chip8;

	// Resolution
	const int width{ 64 };
	const int height{ 32 };
	const int scale{ 10 };

	Interpreter interpreter{};
	interpreter.LoadROM("roms/test1.ch8");
	interpreter.Start();

	cin.get();

	return 0;
}