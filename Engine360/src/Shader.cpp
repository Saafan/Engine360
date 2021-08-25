#include "Shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


Shader::Shader(const char* shaderPath)
{
	std::ifstream file(shaderPath);

	if (!file)
	{
		std::cout << "File: " << shaderPath << " Not Found!" << std::endl;
		return;
	}

	GetShaderCode(file);
	CreateProgram();
	Bind();
}

void Shader::Bind()
{
	glUseProgram(programID);
}

void Shader::GetShaderCode(std::ifstream& file)
{
	std::string line;
	while (std::getline(file, line))
		if (line == "#fragment" || line == "#geometry")
			break;
		else
			shaderData.vertexShader += line + "\n";

	if (line == "#geometry")
		while (std::getline(file, line))
			if (line == "#fragment")
				break;
			else
				shaderData.geometryShader += line + "\n";

	while (std::getline(file, line))
		shaderData.fragmentShader += line + "\n";

	std::cout << "vert: " << shaderData.vertexShader << std::endl;
	std::cout << "frag: " << shaderData.fragmentShader << std::endl;
}

unsigned int Shader::CompileShader(std::string& srcCode, GLenum shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	const GLchar* src = srcCode.c_str();
	glShaderSource(shader, 1, &src, nullptr);

	glCompileShader(shader);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		size_t size = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shader, 2048, nullptr, message);
		std::cout << "Message: " << message << std::endl;
	}
	return shader;
}

void Shader::CreateProgram()
{
	programID = glCreateProgram();

	vertShaderID = CompileShader(shaderData.vertexShader, GL_VERTEX_SHADER);
	fragShaderID = CompileShader(shaderData.fragmentShader, GL_FRAGMENT_SHADER);
	geomShaderID = CompileShader(shaderData.geometryShader, GL_GEOMETRY_SHADER);

	glAttachShader(programID, vertShaderID);
	glAttachShader(programID, fragShaderID);

	glUseProgram(programID);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);
	glDeleteShader(geomShaderID);
}

