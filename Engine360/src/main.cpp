#include <iostream>
#include "Renderer/Renderer.h"
#include "VertexBuffer.h"

int main()
{

	GLFWwindow** window = &Renderer::Get().window;

	if (!glfwInit())
		std::cout << "Initialization of GLFW Failed!" << std::endl;

	Renderer::Get().window = glfwCreateWindow(WIDTH, HEIGHT, "Engine360", nullptr, nullptr);
	glfwMakeContextCurrent(*window);

	if (glewInit() != GLEW_OK)
		std::cout << "Initialization of GLEW Failed!" << std::endl;
	glfwSetInputMode(Renderer::Get().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("Shaders/main.glsl");
	float d[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};
	VertexBuffer vb(&d, sizeof(d));
	Camera c;
	c.Bind();

	vb.InsertStride<float>(3);
	vb.Bind();
	shader.Bind();

	//vb.InsertStride<float>(10,10);
	while (!glfwWindowShouldClose(*window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);

		//Drawing Begins here
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Renderer::Get().curCamera->CalculateViewMatrix();

		glfwSwapBuffers(*window);
	}

}
