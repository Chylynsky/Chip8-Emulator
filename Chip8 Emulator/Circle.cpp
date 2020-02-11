#include "Circle.h"

namespace GraphicsEngine
{
	const float Circle::pi{ 3.14159265358979323846f };
	const int Circle::N{ 8 * 6 };

	Circle::Circle(Window* window, int x, int y, int radius) : Object(window, x, y)
	{
		float currentAngle = 0.0f;
		this->radius = static_cast<float>(radius) / window->GetWindowSize().first;
		// Reserve space for N triangles
		bufferData.reserve(N * 9);

		for (int i = 0; i < N; i++)
		{
			bufferData.push_back(this->x);
			bufferData.push_back(this->y);
			bufferData.push_back(0.0f);

			bufferData.push_back(this->x + this->radius * std::cos(currentAngle));
			bufferData.push_back(this->y + this->radius * std::sin(currentAngle));
			bufferData.push_back(0.0f);

			currentAngle = 2.0f * pi * static_cast<float>(i + 1) / static_cast<float>(N);

			bufferData.push_back(this->x + this->radius * std::cos(currentAngle));
			bufferData.push_back(this->y + this->radius * std::sin(currentAngle));
			bufferData.push_back(0.0f);
		}

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_STATIC_DRAW);
	}

	Circle::~Circle()
	{

	}

	void Circle::Draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, true, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, N * 9); // Draw N triangles
		glDisableVertexAttribArray(0);
	}

	void Circle::Move(int x, int y)
	{
		std::pair<float, float> windowSize = window->GetWindowSize();
		this->x += static_cast<float>(x) / windowSize.first;
		this->y += static_cast<float>(y) / windowSize.second;
		bufferData.clear();

		for (int i = 0; i < N; i++)
		{
			bufferData.push_back(this->x);
			bufferData.push_back(this->y);
			bufferData.push_back(0.0f);

			bufferData.push_back(this->x + this->radius * std::cos(2.0f * pi * static_cast<float>(i) / static_cast<float>(N)));
			bufferData.push_back(this->y + this->radius * std::sin(2.0f * pi * static_cast<float>(i) / static_cast<float>(N)));
			bufferData.push_back(0.0f);

			bufferData.push_back(this->x + this->radius * std::cos(2.0f * pi * static_cast<float>(i + 1) / static_cast<float>(N)));
			bufferData.push_back(this->y + this->radius * std::sin(2.0f * pi * static_cast<float>(i + 1) / static_cast<float>(N)));
			bufferData.push_back(0.0f);
		}

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_DYNAMIC_DRAW);
	}
}