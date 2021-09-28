#include "Renderer/Renderer.h"
#include <iostream>
#include <string>
#include <fstream>
#include "GL/glew.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"

Shader::Shader(const char* shaderPath)
{
	shaderName = shaderPath;
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
	Renderer::Get().SetShader(this);
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
		int size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
		char* message = (char*)malloc(size * sizeof(char));
		glGetShaderInfoLog(shader, size * sizeof(char), nullptr, message);
		std::cout << "Message: " << message << std::endl;
	}
	return shader;
}

void Shader::CreateProgram()
{
	programID = glCreateProgram();

	vertShaderID = CompileShader(shaderData.vertexShader, GL_VERTEX_SHADER);
	glAttachShader(programID, vertShaderID);

	fragShaderID = CompileShader(shaderData.fragmentShader, GL_FRAGMENT_SHADER);
	glAttachShader(programID, fragShaderID);

	if (!shaderData.geometryShader.empty())
	{
		geomShaderID = CompileShader(shaderData.geometryShader, GL_GEOMETRY_SHADER);
		glAttachShader(programID, geomShaderID);
	}

	glLinkProgram(programID);

	int result;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		int size;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &size);
		char* message = (char*)malloc(size * sizeof(char));
		glGetProgramInfoLog(programID, size * sizeof(char), nullptr, message);
		std::cout << "Message: " << message << std::endl;
	}

	glValidateProgram(programID);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);
	glDeleteShader(geomShaderID);
}

void Shader::SetUniform1f(const char* name, float value)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const char* name, int value)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const char* name, float v0, float v1, float v2)
{
	const int location = GetUniformLocation(name);
	if (location != -1)  glUniform3f(location, v0, v1, v2);

}

void Shader::SetUniform3f(const char* name, glm::vec3 value)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniformMat4(const char* name, glm::mat4& value)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformMat4(const char* name, glm::mat4&& value)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformMat4Positioned(const char* name, glm::vec3 pos, glm::mat4 originalPos)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(glm::translate(originalPos, pos)));
}

void Shader::SetUniformMat4Positioned(const char* name, float v0, float v1, float v2, glm::mat4 originalPos)
{
	const int location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(glm::translate(originalPos, glm::vec3(v0, v1, v2))));
}

const char* Shader::GetName()
{
	return shaderName.c_str();
}


float Shader::GetFloatUniform(const char* name)
{
	float value = 0.0f;
	glGetUniformfv(programID, GetUniformLocation(name), &value);
	return value;
}

int Shader::GetIntUniform(const char* name)
{
	int value = 0.0f;
	glGetUniformiv(programID, GetUniformLocation(name), &value);
	return value;
}

glm::vec3 Shader::GetVec3Uniform(const char* name)
{
	glm::vec3 value = glm::vec3(0.0);
	for (size_t i = 0; i < 3; i++)
	{
		float element;
		std::string curName = name ;
		curName += "[";
		curName += std::to_string(i);
		curName += "]";
		
		glGetUniformfv(programID, GetUniformLocation(curName.c_str()), &element);
		value[i] = element;
	}
	return value;
}

glm::vec4 Shader::GetVec4Uniform(const char* name)
{
	glm::vec4 value;
	for (size_t i = 0; i < 4; i++)
	{
		float element;
		const char* curName = name + '.' + (char)('x' + i);
		glGetUniformfv(programID, GetUniformLocation(curName), &element);
		value[i] = element;
	}
	return value;
}

glm::mat4 Shader::GetMat4Uniform(const char* name)
{
	glm::mat4 value;
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
		{
			float element;
			glGetUniformfv(programID, GetUniformLocation(name), &element);
			value[i][j] = element;
		}
	return value;
}

unsigned int Shader::GetUniformLocation(const char* name)
{
	if (list.find(name) == list.end())
	{
		const int location = glGetUniformLocation(programID, name);
		if (location == -1)
		{
			std::cout << "Uniform " << name << " doesn't exist in Shader[ " << shaderName << " ]" << std::endl;
			return -1;
		}
		list[name] = location;
		return location;
	}

	return list[name];
}