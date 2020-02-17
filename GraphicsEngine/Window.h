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
		static const int INITIAL_WIDTH;
		static const int INITIAIL_HEIGHT;
		static const std::string DEFAULT_TITLE;

		GLFWwindow* window;

	public:

		explicit Window(int width = INITIAL_WIDTH, int height = INITIAIL_HEIGHT, std::string title = DEFAULT_TITLE);
		~Window();

		std::pair<int, int> GetWindowSize();
		std::pair<float, float> GetPointNormalized(int x, int y);
		bool WindowShouldClose();
		void SwapBuffers();
		void PollEvents();
	};
}