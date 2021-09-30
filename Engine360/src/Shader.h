#pragma once

#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

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

	const char* GetName();
	unsigned int GetProgramID();

	float GetFloatUniform(const char* name);
	int GetIntUniform(const char* name);
	glm::vec3 GetVec3Uniform(const char* name);
	glm::vec4 GetVec4Uniform(const char* name);
	glm::mat4 GetMat4Uniform(const char* name);

private:
	void GetShaderCode(std::ifstream& file);
	unsigned int CompileShader(std::string& srcCode, unsigned int shaderType);
	ShadersData shaderData;
	std::string shaderName;

	void CreateProgram();

	std::unordered_map<const char*, unsigned int> list;

	unsigned int GetUniformLocation(const char* name);
	unsigned int programID = 0, vertShaderID = 0, fragShaderID = 0, geomShaderID = 0;
};