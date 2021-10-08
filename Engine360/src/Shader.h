#pragma once

#include <string>
#include <unordered_map>
#include "glm/fwd.hpp"

class UniformBase;

struct ShadersData {
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometryShader;
};

class Shader
{
public:
	Shader(const char* shaderPath);
	~Shader();
	void Bind();

	void Report();
	const char* GetName();
	unsigned int GetProgramID();
	std::vector<UniformBase*> uniforms;

private:
	void GetShaderCode(std::ifstream& file);
	unsigned int CompileShader(std::string& srcCode, unsigned int shaderType);
	ShadersData shaderData;
	std::string shaderName;

	void CreateProgram();
	unsigned int programID = 0, vertShaderID = 0, fragShaderID = 0, geomShaderID = 0;
};