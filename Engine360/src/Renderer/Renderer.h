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

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;
constexpr float CAMERA_SPEED = 0.05f;
constexpr float CAMERA_MOTION_SPEED = 0.5f;

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


static GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 