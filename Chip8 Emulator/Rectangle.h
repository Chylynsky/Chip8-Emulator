#pragma once
#include <utility>
#include <cmath>
#include <vector>
#include "GL/glew.h"
#include "Object.h"
#include "Window.h"

namespace GraphicsEngine
{
	class Rectangle : public Object
	{
		// Position in pixels
		int x;
		int y;
		int width;
		int height;
		// Position normalized
		float _x;
		float _y;
		float _width;
		float _height;

		unsigned int vertexBuffer;
		std::vector<float> bufferData;
		Window* window;

	public:

		Rectangle(Window* window, int x, int y, int width, int height);

		void Draw();
		void Move(int x, int y);
	};
}