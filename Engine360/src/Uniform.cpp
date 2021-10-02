#include "Uniform.h"
#include "Shader.h"
#include "glm/glm.hpp"

UniformBase::UniformBase(const char* name, void (*setShaderUniformFunc)())
{
	this->name = name;
	this->setShaderUniformFunc = setShaderUniformFunc;
	uniformLocation = GetUniformLocation();
	if (uniformLocation == -1)
		std::cout << "Uniform " << name << " doesn't exist in Shader[ " << shader->GetName() << " ]" << std::endl;
}

UniformBase::UniformBase(const char* name)
{
	this->name = name;
//	this->setShaderUniformFunc = setShaderUniformFunc;
	uniformLocation = GetUniformLocation();
	if (uniformLocation == -1)
		std::cout << "Uniform " << name << " doesn't exist in Shader[ " << shader->GetName() << " ]" << std::endl;

}

unsigned int UniformBase::GetUniformLocation()
{
	return glGetUniformLocation(shader->GetProgramID(), name);
}

void UniformBase::UpdateShaderUniform()
{
	setShaderUniformFunc();
}
