#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm.hpp"
#include <string>
#include <iostream>

#include "Shader.h"
#include "Camera.h"

#define WIDTH 1280
#define HEIGHT 720

struct Type
{
	Type(GLenum type, size_t size) { this->type = type; this->size = size; };
	GLenum type = 0;
	size_t size = 0;
	unsigned int count = 0;
};

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

	static Renderer& Get() {
		static Renderer renderer;
		return renderer;
	}

	template <typename type>
	static Type&& ConvertTypeToGLType()
	{
		if (typeid(type) == typeid(float)) return Type(GL_FLOAT, sizeof(type));
		if (typeid(type) == typeid(unsigned int)) return Type(GL_UNSIGNED_INT, sizeof(type));
		if (typeid(type) == typeid(int)) return Type(GL_INT, sizeof(type));
		if (typeid(type) == typeid(double)) return Type(GL_DOUBLE, sizeof(type));
		if (typeid(type) == typeid(short)) return Type(GL_SHORT, sizeof(type));
		if (typeid(type) == typeid(unsigned short)) return Type(GL_UNSIGNED_SHORT, sizeof(type));
		if (typeid(type) == typeid(char)) return Type(GL_BYTE, sizeof(type));
		if (typeid(type) == typeid(unsigned char)) return Type(GL_UNSIGNED_BYTE, sizeof(type));
	}

	//GLFW
	GLFWwindow* window = nullptr;

	//Shaders
	Shader* curShader = nullptr;

	//Camera
	Camera* curCamera = nullptr;
	double x, y;
};

