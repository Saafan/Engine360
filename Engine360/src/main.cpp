#include "Renderer/Renderer.h"

int main()
{
	GLFWwindow* &window = Renderer::Get().window;
	if (!glfwInit())
		std::cout << "Initialization of GLFW Failed!" << std::endl;

	Renderer::Get().window = glfwCreateWindow(WIDTH, HEIGHT, "Engine360", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Initialization of GLEW Failed!" << std::endl;
	glfwSetInputMode(Renderer::Get().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("Shaders/main.glsl");

	Camera c;
	c.Bind();

	Model::Cylinder cylinder(1.0f, 3.0f);

	shader.Bind();
	

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		//Drawing Begins here
		Renderer::Get().curCamera->Shoot();
		Renderer::Get().RenderModels();
		Renderer::Get().curShader->SetUniform3f("lightPos", Renderer::Get().curCameraPos);

		glfwSwapBuffers(window);
	}

}
