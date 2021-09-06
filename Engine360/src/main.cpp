#include "Renderer/Renderer.h"
#include "VertexBuffer.h"

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
	

	Model::Cube cube(0.2f, 0.2f, 0.2f);
	Model::Cube cube2(0.2f, 0.2f, 0.2f);
	Model::Cylinder cylinder(1.0f, 3.0f);
	shader.Bind();

	//cube.SetPosition(0,0,0);
	//cube2.SetPosition(0,1,0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);

		//Drawing Begins here
		Renderer::Get().curCamera->Shoot();
		Renderer::Get().RenderModels();

		glfwSwapBuffers(window);
	}

}
