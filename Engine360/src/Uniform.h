#pragma once

#include <memory>
#include "glm/fwd.hpp"
#include "GL/glew.h"
#include "Renderer/Renderer.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "Helpers/Printer.h"

class UniformBase
{
public:
	UniformBase(const char* name, Shader* shader, bool isStatic);
	UniformBase() = default;
	~UniformBase();
	unsigned int GetUniformLocation();
	virtual void UpdateShaderUniform();
	virtual void Report();
protected:
	const char* name = "NULL";
	Shader* shader = nullptr;
	unsigned int uniformLocation = 0;
	bool isStatic = false;
};


template <typename type>
class Uniform : public UniformBase
{
public:
	Uniform(const char* name, type* dataPtr, Shader* shader, unsigned int count = 1, bool isStatic = false);
	Uniform(const char* name, type& data, Shader* shader, unsigned int count = 1, bool isStatic = false);
	Uniform(const char* name, type&& data, Shader* shader, unsigned int count = 1, bool isStatic = false);
	void AddShader(Shader* shader);
	void SetData(type* dataPtr);
	void SetData(type data);
	void UpdateShaderUniform();
	void Report();
private:

	void UpdateShaderUniformHelper();
	type* data = nullptr;
	type oldData = type();
};

template <typename type>
void Uniform<type>::AddShader(Shader* shader)
{
	shader->uniforms.emplace_back(this);
}

template <typename type>
inline
Uniform<type>::Uniform(const char* name, type* dataPtr, Shader* shader, unsigned int count, bool isStatic)
	: UniformBase(name, shader, isStatic)
{
	data = dataPtr;
	if (!isStatic)
	{
		if (shader == nullptr)
			for (const auto& shader : Renderer::Get().shaders)
				shader->uniforms.emplace_back(this);
		else
			shader->uniforms.emplace_back(this);
	}
	else
		UpdateShaderUniform();
}

template <typename type>
inline
Uniform<type>::Uniform(const char* name, type& data, Shader* shader, unsigned int count, bool isStatic)
	: UniformBase(name, shader, isStatic)
{
	this->data = &data;
	if (!isStatic)
	{
		if (shader == nullptr)
			for (const auto& shader : Renderer::Get().shaders)
				shader->uniforms.emplace_back(this);
		else
			shader->uniforms.emplace_back(this);
	}
	else
		UpdateShaderUniform();
}

template <typename type>
inline
Uniform<type>::Uniform(const char* name, type&& data, Shader* shader, unsigned int count, bool isStatic)
	: UniformBase(name, shader, isStatic)
{
	this->data = new type(data);
	if (!isStatic)
	{
		if (shader == nullptr)
			for (const auto& shader : Renderer::Get().shaders)
				shader->uniforms.emplace_back(this);
		else
			shader->uniforms.emplace_back(this);
	}
	else
		UpdateShaderUniform();
}


template <typename type>
void Uniform<type>::UpdateShaderUniform()
{
	if (UniformEquals(*data, oldData))
		return;
	oldData = *data;
	UpdateShaderUniformHelper();
}

template <>
inline
void Uniform<int>::UpdateShaderUniformHelper()
{
	glUniform1i(uniformLocation, *data);
}

template <>
inline
void Uniform<unsigned int>::UpdateShaderUniformHelper()
{
	glUniform1ui(uniformLocation, *data);
}

template <>
inline
void Uniform<float>::UpdateShaderUniformHelper()
{
	glUniform1f(uniformLocation, *data);
}

template <>
inline
void Uniform<glm::vec3>::UpdateShaderUniformHelper()
{
	glUniform3f(uniformLocation, data->x, data->y, data->z);
}

template <>
inline
void Uniform<glm::vec4>::UpdateShaderUniformHelper()
{
	glUniform4f(uniformLocation, data->x, data->y, data->z, data->w);
}

template <>
inline
void Uniform<glm::mat4>::UpdateShaderUniformHelper()
{
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(*data));
}

template <typename type>
inline void Uniform<type>::SetData(type* dataPtr)
{
	this->data = dataPtr;
}

template <typename type>
inline void Uniform<type>::SetData(type data)
{
	this->data = data;
}

template <>
inline
void Uniform<float>::Report()
{
	std::cout << "Name: " << name << " Old Value: " << oldData << std::endl;
	std::cout << "Name: " << name << " New Value: " << *data << std::endl;
}

template <>
inline
void Uniform<int>::Report()
{
	std::cout << "Name: " << name << " Old Value: " << oldData << std::endl;
	std::cout << "Name: " << name << " New Value: " << *data << std::endl;
}

template <>
inline
void Uniform<unsigned int>::Report()
{
	std::cout << "Name: " << name << " Old Value: " << oldData << std::endl;
	std::cout << "Name: " << name << " New Value: " << *data << std::endl;
}

template <>
inline
void Uniform<glm::vec2>::Report()
{
	std::cout << "Name: " << name << " Old Value: (x: " << oldData.x << ", y:" << oldData.y << ")" << std::endl;
	std::cout << "Name: " << name << " New Value: (x: " << data->x << ", y:" << data->y << ")" << std::endl;
}

template <>
inline
void Uniform<glm::vec3>::Report()
{
	std::cout << "Name: " << name << " Old Value: (x: " << oldData.x << ", y:" << oldData.y << ", z:" << oldData.z << ")" << std::endl;
	std::cout << "Name: " << name << " New Value: (x: " << data->x << ", y:" << data->y << ", z:" << data->z << ")" << std::endl;
}

template <>
inline
void Uniform<glm::mat4>::Report()
{
	std::cout << "Name: " << name << " Old Value: " << std::endl;
	PrintMatrix(oldData);
	std::cout << std::endl << "Name: " << name << " New Value: " << std::endl;
	PrintMatrix(*data);
	std::cout << std::endl;
}