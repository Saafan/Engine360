#include "Uniform.h"
#include "Shader.h"
#include "glm/glm.hpp"

UniformBase::UniformBase(const char* name, Shader* shader, bool isStatic)
{
	this->name = name;
	this->isStatic = isStatic;
	this->shader = shader;
	uniformLocation = GetUniformLocation();
	if (uniformLocation == -1)
		std::cout << "Uniform " << name << " doesn't exist in Shader[ " << shader->GetName() << " ]" << std::endl;
}

UniformBase::~UniformBase()
{
	std::vector<UniformBase*>& uniforms = shader->uniforms;
	for (size_t i = 0; i < uniforms.size(); i++)
		if (uniforms.at(i)->name == this->name)
			uniforms.erase(uniforms.begin() + i);
}

unsigned int UniformBase::GetUniformLocation()
{
	return glGetUniformLocation(shader->GetProgramID(), name);
}

void UniformBase::UpdateShaderUniform()
{
	std::cout << "No Uniform has been Assigned Yet!" << std::endl;
}

void UniformBase::Report()
{
	std::cout << "No Uniform to Report" << std::endl;
}
