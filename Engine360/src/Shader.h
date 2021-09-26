#pragma once

#include "glm.hpp"
#include <string>

struct ShadersData {
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometryShader;
};


class Shader
{

public:
	Shader(const char* shaderPath);
	void Bind();
	void SetUniform1f(const char* name, float value);
	void SetUniform3f(const char* name, float v0, float v1, float v2);
	void SetUniform3f(const char* name, glm::vec3 value);
	void SetUniformMat4(const char* name, glm::mat4& value);
	void SetUniformMat4(const char* name, glm::mat4&& value);

	const char* GetName();

private:
	void GetShaderCode(std::ifstream& file);
	unsigned int CompileShader(std::string& srcCode, unsigned int shaderType);
	ShadersData shaderData;
	std::string shaderName;

	void CreateProgram();

	unsigned int GetUniformLocation(const char* name);
	unsigned int programID = 0, vertShaderID = 0, fragShaderID = 0, geomShaderID = 0;
};