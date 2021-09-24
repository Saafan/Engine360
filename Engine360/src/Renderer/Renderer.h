#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;
const double CAMERA_SPEED = 0.05;
const double CAMERA_MOTION_SPEED = 0.5f;

#define SHADER_MODEL "model"
#define SHADER_VIEW "view"
#define SHADER_PROJ "proj"

#define CAMERA_POS "cameraPos"

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

	void RenderModels();
	void RenderModels(Shader& shader);
	void UpdateCameraPosition();

	static Renderer& Get() {
		static Renderer renderer;
		return renderer;
	}

	//GLFW
	GLFWwindow* window = nullptr;

	//Shaders
	Shader* curShader = nullptr;

	//Camera
	Camera* curCamera = nullptr;
	glm::dvec3 curCameraPos = glm::vec3(0.0f, 0.5f, 1.5f);
	double x = 0.0, y = 0.0;

	//Models
	std::vector<Model::Model*> models;
};

inline void Renderer::UpdateCameraPosition()
{
	curShader->SetUniform3f(CAMERA_POS, curCameraPos);
}

inline void Renderer::RenderModels()
{
	for (const auto& model : models)
		if (model->visible)
			model->Render();
}

inline void Renderer::RenderModels(Shader& shader)
{
	Shader* tmp = curShader;
	curShader = &shader;
	shader.Bind();
	curCamera->UpdateViewProjectionMatrix();

	for (const auto& model : models)
		if (model->visible)
			model->Render();
	
	curShader = tmp;
	tmp->Bind();
}