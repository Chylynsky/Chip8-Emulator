#include "Renderer.h"
#include <iostream>

using namespace std;
using namespace GraphicsEngine;

int main()
{
	Window window;
	Renderer renderer(&window);

	renderer.Run();

	return 0;
}