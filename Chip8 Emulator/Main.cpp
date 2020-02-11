#include <thread>
#include "GraphicsEngine.h"

using namespace GraphicsEngine;

int main()
{
	Window window(600, 600, "Squares");
	Renderer renderer(&window);

	Circle cir(&window, 300, 300, 100);
	Rectangle rec(&window, 200, 100, 100, 100);

	renderer.Attach(&cir);
	renderer.Attach(&rec);

	while (!window.WindowShouldClose())
	{
		renderer.Render();
		window.SwapBuffers();
		window.PollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}