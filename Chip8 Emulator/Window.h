#pragma once
#include <exception>
#include <stdexcept>
#include <utility>
#include <string>
#include "GLFW/glfw3.h"

namespace GraphicsEngine
{
	class Window
	{
		static const int initWidth;
		static const int initHeight;
		static const std::string defaultTitle;

		GLFWwindow* window;

	public:

		explicit Window(int width = initWidth, int height = initHeight, std::string title = defaultTitle);
		~Window();

		std::pair<int, int> GetWindowSize();
		std::pair<float, float> GetPointNormalized(int x, int y);
		bool WindowShouldClose();
		void SwapBuffers();
		void PollEvents();
	};
}