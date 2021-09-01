#include <iostream>
#include "Renderer/Renderer.h"
#include "Shader.h"
#include <unordered_map>
#include "VertexBuffer.h"
#include <typeinfo>
int main()
{

	GLFWwindow** window = &Renderer::Get().window;

	if (!glfwInit())
		std::cout << "Initialization of GLFW Failed!" << std::endl;

	Renderer::Get().window = glfwCreateWindow(WIDTH, HEIGHT, "Engine360", nullptr, nullptr);
	glfwMakeContextCurrent(*window);

	if (glewInit() != GLEW_OK)
		std::cout << "Initialization of GLEW Failed!" << std::endl;

	Shader shader("Shaders/main.glsl");
	float d[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};
	VertexBuffer vb(&d, sizeof(d));
	vb.InsertStride<float>(3);
	//vb.InsertStride<float>();
	//vb.InsertStride<float>(4);
	vb.Bind();
	//vb.InsertStride<float>(10,10);
	while (!glfwWindowShouldClose(*window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);

		//Drawing Begins here
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(*window);
	}

}
