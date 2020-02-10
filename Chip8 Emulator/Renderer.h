#pragma once
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <cmath>
#include "GL/glew.h"
#include "Window.h"
#include "ShaderLoader.h"

namespace GraphicsEngine
{
	class Renderer
	{
		static const int initWidth;
		static const int initHeight;
		static const char* defaultTitle;

		Window* window;

	public:

		Renderer(Window* window);
		~Renderer();

		void Run();
		void DrawRectangle(int x, int y, int width, int height);
	};
}