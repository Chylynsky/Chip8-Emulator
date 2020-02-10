#include "Renderer.h"

namespace GraphicsEngine
{
	void Renderer::Render()
	{
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use the shaders
		glUseProgram(shaderProgramID);

		for (auto elem : objects)
			elem->Draw();
	}

	Renderer::Renderer(Window* window) : window{ window }
	{
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("GLEW could not be initialized.");

		unsigned int VertexArrayID = 0;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Load shaders
		shaderProgramID = ShaderLoader::GetShaderProgram("VertexShader.glsl", "FragmentShader.glsl");
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Attach(Rectangle* object)
	{
		objects.push_back(object);
	}
}