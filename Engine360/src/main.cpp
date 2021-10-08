#include "Renderer/Renderer.h"

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"

int main()
{
	GLFWwindow*& window = Renderer::Get().window;
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
	Shader shader("Shaders/main.glsl");
	shader.Bind();

	Model::Cube cube(1.0f, 1.0f, 1.0f);
	Camera c;
	c.Bind();

	Texture tex("images/container.png");
	tex.Bind();

	Light::PointLight(glm::vec3(3.0f), &shader);

	Uniform<glm::vec3> lightPosUniform("lightPos", glm::vec3(2, 2, 2), Renderer::Get().curShader, true);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		//Drawing Begins here
		Renderer::Get().curCamera->Shoot();

		shader.Bind();
		Renderer::Get().RenderModels();

		glfwSwapBuffers(window);
	}

}