#pragma once
#include <cmath>
#include <vector>
#include "GL/glew.h"
#include "Object.h"
#include "Window.h"

namespace GraphicsEngine
{
	class Circle : public Object
	{
		static const float PI;
		// Number of triangles that form a circle
		static const int N;

		// Radius normalized
		float radius;

	public:

		Circle(Window* window, int x, int y, int radius);
		~Circle();

		void Draw() override;
		void Move(int x, int y) override;
	};
}