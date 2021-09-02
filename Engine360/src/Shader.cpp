#include "Renderer/Renderer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "GL/glew.h"
#include <gtc/type_ptr.hpp>

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
	Renderer::Get().curShader = this;
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

}

unsigned int Shader::CompileShader(std::string& srcCode, unsigned int shaderType)
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

	glLinkProgram(programID);
	glValidateProgram(programID);

	glUseProgram(programID);
	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);
	glDeleteShader(geomShaderID);
}

void Shader::SetUniform1f(const char* name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4(const char* name, glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformMat4(const char* name, glm::mat4&& value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::GetUniformLocation(const char* name)
{
	static std::unordered_map<const char*, unsigned int> list;
	
	if (list.find(name) == list.end())
	{
		const unsigned int location = glGetUniformLocation(programID, name);
		list[name] = location;
		return location;
	}
	else
		return list[name];
}