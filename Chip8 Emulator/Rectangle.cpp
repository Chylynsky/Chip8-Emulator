#include "Rectangle.h"

namespace GraphicsEngine
{
	Rectangle::Rectangle(Window* window, int x, int y, int width, int height) : x{ x }, y{ y }, width{ width }, height{ height }, vertexBuffer{ 0 }
	{
		std::pair<float, float> tmp = window->GetPointNormalized(x, y);

		float xNormalized = tmp.first;
		float yNormalized = tmp.second;

		float widthNormalized = static_cast<float>(width) / static_cast<float>(window->GetWindowSize().first);
		float heightNormalized = static_cast<float>(height) / static_cast<float>(window->GetWindowSize().second);

		float buffer_data[]
		{
			xNormalized, yNormalized, 0.0f,
			xNormalized, yNormalized + heightNormalized, 0.0f,
			xNormalized + widthNormalized, yNormalized + heightNormalized, 0.0f,
			xNormalized, yNormalized, 0.0f,
			xNormalized + widthNormalized, yNormalized, 0.0f,
			xNormalized + widthNormalized, yNormalized + heightNormalized, 0.0f,
		};

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	}

	void Rectangle::Draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 2 triangles
		glDisableVertexAttribArray(0);
	}
}