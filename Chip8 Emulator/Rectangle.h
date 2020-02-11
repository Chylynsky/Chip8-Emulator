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
		// Diameters normalized
		float width;
		float height;

	public:

		Rectangle(Window* window, int x, int y, int width, int height);
		~Rectangle();

		void Draw() override;
		void Move(int x, int y) override;
	};
}