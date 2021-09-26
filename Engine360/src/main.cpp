#include "Renderer/Renderer.h"

Shader* curShader = Renderer::Get().curShader;

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

	Shader shaderNormal("Shaders/normals.glsl");
	Shader shader("Shaders/main.glsl");

	//Model::Cube cube(1.0f, 1.0f, 3.0f);
	Model::Cone cone(1.0f, 3.0f);

	Camera c;
	c.Bind();
	
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		//Drawing Begins here
		Renderer::Get().curCamera->Shoot();
		shader.Bind();
		Renderer::Get().curCamera->UpdateViewProjectionMatrix();
		Renderer::Get().RenderModels();

		shaderNormal.Bind();
		Renderer::Get().curCamera->UpdateViewProjectionMatrix();
		Renderer::Get().RenderModels();


		glfwSwapBuffers(window);
	}

}
