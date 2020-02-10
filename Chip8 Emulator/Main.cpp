#include <thread>
#include "GraphicsEngine.h"

using namespace GraphicsEngine;

int main()
{
	Window window(960, 540, "Sqaures");
	Renderer renderer(&window);

	Rectangle rec1(&window, 100, 100, 100, 100);
	Rectangle rec2(&window, 200, 200, 100, 100);
	Rectangle rec3(&window, 300, 300, 100, 100);

	renderer.Attach(&rec1);
	renderer.Attach(&rec2);
	renderer.Attach(&rec3);

	while (!window.WindowShouldClose())
	{
		renderer.Render();
		window.SwapBuffers();
		window.PollEvents();

		rec1.Move(2, 0);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}