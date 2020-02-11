#include "Rectangle.h"

namespace GraphicsEngine
{
	Rectangle::Rectangle(Window* window, int x, int y, int width, int height) : Object(window, x, y)
	{
		std::pair<float, float> windowSize = window->GetWindowSize();

		this->width = static_cast<float>(width) / windowSize.first;
		this->height = static_cast<float>(height) / windowSize.second;

		bufferData = 
		{
			this->x, this->y, 0.0f,
			this->x, this->y + this->height, 0.0f,
			this->x + this->width, this->y + this->height, 0.0f,
			this->x, this->y, 0.0f,
			this->x + this->width, this->y, 0.0f,
			this->x + this->width, this->y + this->height, 0.0f
		};

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_DYNAMIC_DRAW);
	}

	Rectangle::~Rectangle()
	{
	}

	void Rectangle::Draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, true, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 2 triangles
		glDisableVertexAttribArray(0);
	}

	void Rectangle::Move(int dx, int dy)
	{
		std::pair<float, float> windowSize = window->GetWindowSize();

		x += static_cast<float>(dx) / windowSize.first;
		y += static_cast<float>(dy) / windowSize.first;

		bufferData = 
		{
			this->x, this->y, 0.0f,
			this->x, this->y + this->height, 0.0f,
			this->x + this->width, this->y + this->height, 0.0f,
			this->x, this->y, 0.0f,
			this->x + this->width, this->y, 0.0f,
			this->x + this->width, this->y + this->height, 0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_DYNAMIC_DRAW);
	}
}