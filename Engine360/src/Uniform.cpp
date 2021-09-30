#include "Uniform.h"
#include "Shader.h"
#include "Renderer/Renderer.h"
#include "glm/gtc/type_ptr.hpp"


inline UniformBase::UniformBase(const char* name, void (*setShaderUniformFunc)())
{
	this->name = name;
	this->setShaderUniformFunc = setShaderUniformFunc;
	uniformLocation = GetUniformLocation();
	if (uniformLocation == -1)
		std::cout << "Uniform " << name << " doesn't exist in Shader[ " << shader->GetName() << " ]" << std::endl;
}

inline unsigned int UniformBase::GetUniformLocation()
{
	return glGetUniformLocation(shader->GetProgramID(), name);
}

inline void UniformBase::UpdateShaderUniform()
{
	setShaderUniformFunc();
}

template <typename type>
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
void Uniform<int>::UpdateShaderUniformHelper()
{
	glUniform1i(uniformLocation, data);
}

template <>
void Uniform<unsigned int>::UpdateShaderUniformHelper()
{
	glUniform1ui(uniformLocation, data);
}

template <>
void Uniform<float>::UpdateShaderUniformHelper()
{
	glUniform1f(uniformLocation, data);
}

template <>
void Uniform<glm::vec3>::UpdateShaderUniformHelper()
{
	glUniform3f(uniformLocation, data.x, data.y, data.z);
}

template <>
void Uniform<glm::vec4>::UpdateShaderUniformHelper()
{
	glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
}

template <>
void Uniform<glm::mat4>::UpdateShaderUniformHelper()
{
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(data));
}

template <typename type>
Uniform<type>::Uniform(const char* name, type* dataPtr, Shader* shader, bool isStatic)
{
	UniformBase uniformFunctionPtr(name, &UpdateShaderUniformHelper);
	if (!isStatic)
		Renderer::Get().uniforms.push_back(UniformBase(uniformFunctionPtr));
	&data = dataPtr;
	this->shader = shader;
	this->isStatic = isStatic;
	this->referenceExist = true;
}

template <typename type>
Uniform<type>::Uniform(const char* name, type data, Shader* shader, bool isStatic /*= false*/)
{
	UniformBase uniformFunctionPtr(name, &UpdateShaderUniformHelper);
	if (!isStatic)
		Renderer::Get().uniforms.push_back(UniformBase(uniformFunctionPtr));
	this->data = data;
	this->shader = shader;
	this->isStatic = isStatic;
	this->referenceExist = false;
}

template <typename type>
void Uniform<type>::SetData(type* dataPtr)
{
	this->data = dataPtr;
	this->referenceExist = true;
	isChanged = true;
}

template <typename type>
void Uniform<type>::SetData(type data)
{
	this->data = data;
	this->referenceExist = false;
	isChanged = true;
}