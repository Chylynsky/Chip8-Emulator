#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

namespace GraphicsEngine
{
	class ShaderLoader
	{
		class TextFile
		{
			std::ifstream file;
			std::string content;

		public:

			explicit TextFile(const std::string& path);
			~TextFile();
			std::string& Read();
		};

	public:

		static unsigned int GetShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	};
}