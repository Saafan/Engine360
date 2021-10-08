#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "Helpers/Printer.h"
#include "glm/fwd.hpp"
#include "UniformBlock.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;
const float CAMERA_SPEED = 0.05f;
const float CAMERA_MOTION_SPEED = 0.5f;

#define SHADER_MODEL "model"
#define SHADER_VIEW "view"
#define SHADER_PROJ "proj"

#define SHADER_CAMERA_POS "cameraPos"

#define SHADER_LIGHT_POSITION "lightPos"
#define SHADER_LIGHT_BLOCK "lights"
#define SHADER_DIRECTIONAL_LIGHT "dirLight"
#define SHADER_POINT_LIGHT "pointLight"
#define SHADER_SPOT_LIGHT "spotLight"

#define SHADER_POINT_LIGHT_BINDING_POINT 1
#define SHADER_DIRECTIONAL_LIGHT_BINDING_POINT 2
#define SHADER_SPOT_LIGHT_BINDING_POINT 3


#define SHADER_POINT_LIGHT_BLOCK "pointLightsBlock"
#define SHADER_DIRECTIONAL_LIGHT_BLOCK "dirLightsBlock"
#define SHADER_SPOT_LIGHT_BLOCK "spotLightBlock"

#define MAX_NR_LIGHTS 5

#define SHADER_TEXTURE_SLOT "textureSlot"

const std::map<std::string, std::string> shaderMacros
{
	{"MAX_NR_LIGHTS", std::to_string(MAX_NR_LIGHTS)}
};

class UniformBase;
namespace Model { class Model; }
class Camera;
class Shader;

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;

	void RenderModels();
	void RenderModels(Shader& shader);

	//Setters and Getters
	void SetShader(Shader* shader);
	static Renderer& Get() {
		static Renderer renderer;
		return renderer;
	}

	//GLFW
	GLFWwindow* window = nullptr;

	//Shaders
	Shader* curShader = nullptr;
	std::vector<Shader*> shaders;
	std::vector<UniformBlock*> uniformBlocks;

	//Camera
	Camera* curCamera = nullptr;
	glm::vec3* curCameraPos;
	double x = 0.0, y = 0.0;


	//Models
	std::vector<Model::Model*> models;
};
