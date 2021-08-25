#include <iostream>
#include "Renderer/Renderer.h"
#include "Shader.h"

int main()
{
	GLFWwindow* window = Renderer::Get().window;

	if (!glfwInit())
		std::cout << "Initialization of GLFW Failed!" << std::endl;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Engine360", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Initialization of GLEW Failed!" << std::endl;

	Shader shader("Shaders/meow.glsl");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);



		glfwSwapBuffers(window);
	}

}
