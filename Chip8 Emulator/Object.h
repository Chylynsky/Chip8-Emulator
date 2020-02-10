#pragma once

namespace GraphicsEngine
{
	class Object
	{
		float x;
		float y;

	public:

		Object();
		Object(float x, float y);

		virtual ~Object();
		virtual void Draw() = 0;
	};
}