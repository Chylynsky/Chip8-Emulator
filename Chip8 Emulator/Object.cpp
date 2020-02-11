#include "Object.h"

namespace GraphicsEngine
{
	Object::Object(Window* window, int x, int y) : window{ window }, vertexBuffer{ 0 }
	{
		std::pair<float, float> positionNormalized = window->GetPointNormalized(x, y);
		this->x = positionNormalized.first;
		this->y = positionNormalized.second;
	}

	Object::~Object()
	{

	}
}