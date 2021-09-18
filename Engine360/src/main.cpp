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
	

	//Model::Cube cube(0.2f, 0.2f, 0.2f);
	//Model::Cube cube2(0.2f, 0.2f, 0.2f);
	Model::Cylinder cylinder(1.0f, 3.0f);
	//Model::Plane plane();
	shader.Bind();

	//cube.SetPosition(0,-3,0);
	//cube2.SetPosition(0,3,0);

	float cube[] =
	{
		//Position
		-0.5f , -0.5f , -0.5f,
		 0.5f , -0.5f , -0.5f,
		 0.5f ,  0.5f , -0.5f,
		 0.5f ,  0.5f , -0.5f,
		-0.5f ,  0.5f , -0.5f,
		-0.5f , -0.5f , -0.5f,

		//Normals
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		//UV Texturing
		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
	};


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
