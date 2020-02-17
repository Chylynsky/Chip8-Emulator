#include "ShaderLoader.h"

GraphicsEngine::ShaderLoader::TextFile::TextFile(const std::string& path)
{
	file.open(path, std::ios::in);
	if (!file.is_open())
		throw std::runtime_error("File " + path + " could not be opened.");
}

GraphicsEngine::ShaderLoader::TextFile::~TextFile()
{
	file.close();
}

std::string& GraphicsEngine::ShaderLoader::TextFile::Read()
{
	std::stringstream sstr;
	sstr << file.rdbuf();
	content = sstr.str();

	return content;
}

unsigned int GraphicsEngine::ShaderLoader::GetShaderProgram(const std::string& vertexShaderLoadPath, const std::string& fragmentShaderLoadPath)
{
	// Create the shaders
	unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	{
		// Read the Vertex Shader code from the file
		TextFile vertexShaderFile(vertexShaderLoadPath);
		vertexShaderCode = vertexShaderFile.Read();

		// Read the Fragment Shader code from the file
		TextFile fragmentShaderFile(fragmentShaderLoadPath);
		fragmentShaderCode = fragmentShaderFile.Read();
	}

	int Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	char const* VertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	// Compile Fragment Shader
	char const* FragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	// Link the program
	unsigned int ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
