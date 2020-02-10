#include "Renderer.h"

namespace GraphicsEngine
{
	Renderer::Renderer(Window* window) : window{ window }
	{
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("GLEW could not be initialized.");

		unsigned int VertexArrayID = 0;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Run()
	{
		/*static const float g_vertex_buffer_data[]
		{
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		// This will identify our vertex buffer
		unsigned int vertexbuffer = 0;
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexbuffer);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);*/

		DrawRectangle(200, 200, 100, 100);

		// Load shaders
		unsigned int programID = 0;
		programID = ShaderLoader::GetShaderProgram("VertexShader.glsl", "FragmentShader.glsl");

		while (!window->WindowShouldClose())
		{
			glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Use the shaders
			glUseProgram(programID);

			// 1st attribute buffer : vertices
			glEnableVertexAttribArray(0);
			//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 6 vertices total -> 2 triangles
			glDisableVertexAttribArray(0);

			window->SwapBuffers();
			window->PollEvents();

			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}

	void Renderer::DrawRectangle(int x, int y, int width, int height)
	{
		std::pair<float, float> tmp = window->GetPointNormalized(x, y);

		float xNormalized = tmp.first;
		float yNormalized = tmp.second;

		tmp = window->GetPointNormalized(width, height);

		float widthNormalized = std::abs(tmp.first);
		float heightNormalized = std::abs(tmp.second);

		float buffer_data[]
		{
			xNormalized, yNormalized, 0.0f,
			xNormalized, yNormalized + heightNormalized, 0.0f,
			xNormalized + widthNormalized, yNormalized + heightNormalized, 0.0f,
			xNormalized, yNormalized, 0.0f,
			xNormalized + widthNormalized, yNormalized, 0.0f,
			xNormalized + widthNormalized, yNormalized + heightNormalized, 0.0f,
		};

		// This will identify our vertex buffer
		unsigned int vertexbuffer = 0;
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexbuffer);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	}
}