#include <iostream>
#include <thread>
#include "CPU.h"

using namespace std;
using namespace Chip8;

int main()
{
	RAM& ram{ RAM::GetInstance() };
	CPU& cpu{ CPU::GetInstance() };

	try 
	{
		ram.LoadFile("test.ch8");
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}

	while (true)
	{
		cpu.Execute();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	return 0;
}