#pragma once

class Shader;
#include "glm/fwd.hpp"
#include "GL/glew.h"
#include "Renderer/Renderer.h"
#include "glm/gtc/type_ptr.hpp"

class UniformBase
{
public:
	UniformBase(const char* name, void (*setShaderUniformFunc)());
	UniformBase(const char* name);
	UniformBase() = default;
	unsigned int GetUniformLocation();
	void UpdateShaderUniform();
	bool isChanged = true;
	bool isStatic = false;

protected:
	unsigned int uniformLocation = 0;
	Shader* shader = nullptr;
	const char* name = "NULL";
	void (*setShaderUniformFunc)() = nullptr;
};


template <typename type>
class Uniform : public UniformBase
{
public:
	Uniform(const char* name, type* dataPtr, Shader* shader, bool isStatic = false);
	Uniform(const char* name, type data, Shader* shader, bool isStatic = false);
	void SetData(type* dataPtr);
	void SetData(type data);
	void UpdateShaderUniform();

private:
	void UpdateShaderUniformHelper();
	type data;
	type oldData;
};


template <typename type>
inline
void Uniform<type>::UpdateShaderUniform()
{
	if (!isChanged && data != oldData)
		isChanged = true;
	oldData = data;

	if (isChanged && uniformLocation != -1)
		UpdateShaderUniformHelper();
	isChanged = false;
}

template <>
inline
void Uniform<int>::UpdateShaderUniformHelper()
{
	glUniform1i(uniformLocation, data);
}

template <>
inline
void Uniform<unsigned int>::UpdateShaderUniformHelper()
{
	glUniform1ui(uniformLocation, data);
}

template <>
inline
void Uniform<float>::UpdateShaderUniformHelper()
{
	glUniform1f(uniformLocation, data);
}

template <>
inline
void Uniform<glm::vec3>::UpdateShaderUniformHelper()
{
	glUniform3f(uniformLocation, data.x, data.y, data.z);
}

template <>
inline
void Uniform<glm::vec4>::UpdateShaderUniformHelper()
{
	glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
}

template <>
inline
void Uniform<glm::mat4>::UpdateShaderUniformHelper()
{
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(data));
}

template <typename type>
inline
Uniform<type>::Uniform(const char* name, type* dataPtr, Shader* shader, bool isStatic)
{
	this->shader = shader;
	this->isStatic = isStatic;
	setShaderUniformFunc = &Uniform::UpdateShaderUniformHelper;
	if (!isStatic)
		Renderer::Get().uniforms.push_back(this);
	data = *dataPtr;
}

template <typename type>
Uniform<type>::Uniform(const char* name, type data, Shader* shader, bool isStatic)
{
	this->shader = shader;
	this->isStatic = isStatic;
	if (!isStatic)
		Renderer::Get().uniforms.push_back(this);
	this->data = data;
}

template <typename type>
inline void Uniform<type>::SetData(type* dataPtr)
{
	this->data = dataPtr;
	isChanged = true;
}

template <typename type>
inline void Uniform<type>::SetData(type data)
{
	this->data = data;
	isChanged = true;
}
