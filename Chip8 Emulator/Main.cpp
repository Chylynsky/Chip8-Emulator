#include "GraphicsEngine.h"
#include <iostream>

using namespace std;
using namespace GraphicsEngine;

int main()
{
	try
	{
		Window window;
		window.PollEvents();
	}
	catch (runtime_error & e)
	{
		cout << e.what() << endl;
	}

	return 0;
}