#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <fstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace GraphicsEngine
{
	class Window
	{
		static const int initWidth;
		static const int initHeight;
		static const char* defaultTitle;

		GLFWwindow* window;

		unsigned int LoadShaders(const std::string& vertexShaderLoadPath, const std::string& fragmentShaderLoadPath);

	public:

		Window();
		~Window();

		void PollEvents();
	};
}