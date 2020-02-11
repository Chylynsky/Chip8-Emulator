#pragma once
#include <utility>
#include <vector>
#include "Window.h"

namespace GraphicsEngine
{
	class Object
	{
	protected:
		// Pointer to the Window object
		Window* window;
		// Position normalized
		float x;
		float y;

		unsigned int vertexBuffer;
		std::vector<float> bufferData;

	public:

		Object(Window* window, int x, int y);
		virtual ~Object();
		virtual void Draw() = 0;
		virtual void Move(int x, int y) = 0;
	};
}