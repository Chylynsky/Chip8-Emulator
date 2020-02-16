#pragma once
#include <exception>
#include <stdexcept>
#include <vector>
#include "GL/glew.h"
#include "Window.h"
#include "ShaderLoader.h"
#include "Object.h"

namespace GraphicsEngine
{
	class Renderer
	{
		Window* window;
		unsigned int shaderProgramID;
		std::vector<Object*> objects;

	public:

		Renderer(Window* window);
		~Renderer();

		void Attach(Object* object);
		void RenderCurrent();
	};
}