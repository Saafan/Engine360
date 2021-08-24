#pragma once
#include "GL\glew.h"
#include "glfw\glfw3.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

	static Renderer& Get() { 
		static Renderer renderer;
		return renderer;
	}
	
	GLFWwindow* window = nullptr;

};

