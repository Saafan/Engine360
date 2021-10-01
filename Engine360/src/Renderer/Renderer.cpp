#include "glm/glm.hpp"
#include "Renderer.h"

#include"Model.h"
#include "Shader.h"
#include "Uniform.h"

void Renderer::SetShader(Shader* shader)
{
	curShader = shader;
}

Renderer::Renderer()
{
	*curCameraPos = glm::vec3(0.0f, 0.5f, 1.5f);
}

void Renderer::RenderModels()
{
	for (const auto& uniform : uniforms)
		if (uniform.isChanged)
			uniform.UpdateShaderUniform();
	for (const auto& model : models)
		if (model->visible)
			model->Render();
}

void Renderer::RenderModels(Shader& shader)
{
	Shader* tmp = curShader;
	curShader = &shader;
	shader.Bind();

	for (const auto& model : models)
		if (model->visible)
			model->Render();

	curShader = tmp;
	tmp->Bind();
}


