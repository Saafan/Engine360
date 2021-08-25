#pragma once

#include "Renderer/Renderer.h"

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


private:
	void GetShaderCode(std::ifstream& file);
	unsigned int CompileShader(std::string& srcCode, GLenum shaderType);
	ShadersData shaderData;

	void CreateProgram();

	unsigned int programID, vertShaderID, fragShaderID, geoShaderID;
};