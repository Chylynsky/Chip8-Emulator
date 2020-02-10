#pragma once
#include <utility>
#include <cmath>
#include "GL/glew.h"
#include "Object.h"
#include "Window.h"

namespace GraphicsEngine
{
	class Rectangle : public Object
	{
		int x;
		int y;
		int width;
		int height;
		unsigned int vertexBuffer;

	public:

		Rectangle(Window* window, int x, int y, int width, int height);

		void Draw();
	};
}