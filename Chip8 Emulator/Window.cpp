#include "Window.h"

namespace GraphicsEngine
{
	const int Window::INITIAIL_HEIGHT{ 400 };
	const int Window::INITIAL_WIDTH{ 600 };
	const std::string Window::DEFAULT_TITLE{ "GLFW Window" };

	Window::Window(int width, int height, std::string title)
	{
		if (!glfwInit())
			throw std::runtime_error("GLFW could not be initialized.");

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (!window)
			throw std::runtime_error("Window could not be initialized.");

		glfwMakeContextCurrent(window);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}
	
	std::pair<int, int> Window::GetWindowSize()
	{
		int width = 0;
		int height = 0;

		glfwGetWindowSize(window, &width, &height);

		return std::pair<int, int>(width, height);
	}

	std::pair<float, float> Window::GetPointNormalized(int x, int y)
	{
		int width = 0;
		int height = 0;

		glfwGetWindowSize(window, &width, &height);

		// Get half of width and height as float
		float halfWidth = static_cast<float>(width) / 2.0f;
		float halfHeight = static_cast<float>(height) / 2.0f;

		// Calculate normalized pozistion
		return std::pair<float, float> 
		(
			(x < halfWidth) ? -(halfWidth - x) / halfWidth : (x - halfWidth) / halfWidth,
			(y < halfHeight) ? (halfHeight - y) / halfHeight : -(y - halfHeight) / halfHeight
		);
	}

	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
}