#include "Shader.h"
#include "Renderer/Renderer.h"

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
	Renderer::Get().shaders.emplace_back(this);
}

Shader::~Shader()
{
	std::vector<Shader*>& shaders = Renderer::Get().shaders;
	for (size_t i = 0; i < shaders.size(); i++)
		if (shaders.at(i) == this)
			shaders.erase(shaders.begin() + i);
}

void Shader::Bind()
{
	glUseProgram(programID);
	Renderer::Get().SetShader(this);
}

void Shader::Report()
{
	std::cout << "Name: " << shaderName << std::endl;
	std::cout << "Vertex Shader: " << shaderData.vertexShader << std::endl << std::endl;
	std::cout << "Geometry Shader: " << shaderData.geometryShader << std::endl << std::endl;
	std::cout << "Fragment Shader: " << shaderData.fragmentShader << std::endl << std::endl;
}

std::string ReplaceMacros(std::string& line)
{
	for (const auto& macro : shaderMacros)
	{
		size_t pos = line.find(macro.first);
		if (pos != std::string::npos)
		{
			line.replace(pos, macro.first.length(), macro.second);
			ReplaceMacros(line);
		}
	}
	return line;
}

void Shader::GetShaderCode(std::ifstream& file)
{
	std::string line;
	while (std::getline(file, line))
		if (line == "#fragment" || line == "#geometry")
			break;
		else
			shaderData.vertexShader += ReplaceMacros(line) + "\n";

	if (line == "#geometry")
		while (std::getline(file, line))
			if (line == "#fragment")
				break;
			else
				shaderData.geometryShader += ReplaceMacros(line) + "\n";

	while (std::getline(file, line))
		shaderData.fragmentShader += ReplaceMacros(line) + "\n";

}

const char* GetShaderTypeName(unsigned int shaderType)
{
	if (shaderType == GL_FRAGMENT_SHADER)
		return "Fragment Shader";
	if (shaderType == GL_VERTEX_SHADER)
		return "Vertex Shader";
	else
		return "Geometry Shader";
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
		const char* shaderTypeName = GetShaderTypeName(shaderType);

		std::cout << "Message: " << "File: " << shaderName << "  " << shaderTypeName << message << std::endl;
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


const char* Shader::GetName()
{
	return shaderName.c_str();
}

unsigned int Shader::GetProgramID()
{
	return programID;
}