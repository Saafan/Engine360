#include "Renderer/Renderer.h"

int main()
{
	GLFWwindow* &window = Renderer::Get().window;
	if (!glfwInit())
		std::cout << "Initialization of GLFW Failed!" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Renderer::Get().window = glfwCreateWindow(WIDTH, HEIGHT, "Engine360", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Initialization of GLEW Failed!" << std::endl;

	glfwSetInputMode(Renderer::Get().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shaderNormal("Shaders/normals.glsl");
	Shader shader("Shaders/main.glsl");
	shader.Bind();

	Model::Cube cone(1.0f, 1.0f, 1.0f);
	Camera c;
	c.Bind();
	Texture tex("images/container.png");
	tex.Bind();
	
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

		//shaderNormal.Bind();
		//Renderer::Get().curCamera->UpdateViewProjectionMatrix();
		//Renderer::Get().RenderModels();

		glfwSwapBuffers(window);
	}

}
