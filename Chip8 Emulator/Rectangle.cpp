#include "Rectangle.h"

namespace GraphicsEngine
{
	Rectangle::Rectangle(Window* window, int x, int y, int width, int height) : x{ x }, y{ y }, width{ width }, height{ height }, vertexBuffer{ 0 }, window{ window }
	{
		std::pair<float, float> tmp = window->GetPointNormalized(x, y);

		_x = tmp.first;
		_y = tmp.second;

		_width = static_cast<float>(width) / static_cast<float>(window->GetWindowSize().first);
		_height = static_cast<float>(height) / static_cast<float>(window->GetWindowSize().second);

		bufferData = std::vector<float>
		{
			_x, _y, 0.0f,
			_x, _y + _height, 0.0f,
			_x + _width, _y + _height, 0.0f,
			_x, _y, 0.0f,
			_x + _width, _y, 0.0f,
			_x + _width, _y + _height, 0.0f
		};

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_DYNAMIC_DRAW);
	}

	void Rectangle::Draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 2 triangles
		glDisableVertexAttribArray(0);
	}

	void Rectangle::Move(int dx, int dy)
	{
		x += dx;
		y += dy;
		_x += static_cast<float>(dx) / window->GetWindowSize().first;
		_y += static_cast<float>(dy) / window->GetWindowSize().second;

		bufferData = std::vector<float>
		{
			_x, _y, 0.0f,
			_x, _y + _height, 0.0f,
			_x + _width, _y + _height, 0.0f,
			_x, _y, 0.0f,
			_x + _width, _y, 0.0f,
			_x + _width, _y + _height, 0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_DYNAMIC_DRAW);
	}
}