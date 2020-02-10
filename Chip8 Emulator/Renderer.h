#pragma once
#include <exception>
#include <stdexcept>
#include <vector>
#include "GL/glew.h"
#include "Window.h"
#include "ShaderLoader.h"
#include "Rectangle.h"

namespace GraphicsEngine
{
	class Renderer
	{
		Window* window;
		unsigned int shaderProgramID;
		std::vector<Rectangle*> objects;

	public:

		Renderer(Window* window);
		~Renderer();

		void Attach(Rectangle* object);
		void Render();
	};
}