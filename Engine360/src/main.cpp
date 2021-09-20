#include "Renderer/Renderer.h"

float cube[] =
{
-0.5f , -0.5f , -0.5f , 
 0.5f , -0.5f , -0.5f , 
 0.5f ,  0.5f , -0.5f , 
 0.5f ,  0.5f , -0.5f , 
-0.5f ,  0.5f , -0.5f , 
-0.5f , -0.5f , -0.5f , 
						
-0.5f , -0.5f ,  0.5f , 
 0.5f , -0.5f ,  0.5f , 
 0.5f ,  0.5f ,  0.5f , 
 0.5f ,  0.5f ,  0.5f , 
-0.5f ,  0.5f ,  0.5f , 
-0.5f , -0.5f ,  0.5f , 
						
-0.5f ,  0.5f ,  0.5f , 
-0.5f ,  0.5f , -0.5f , 
-0.5f , -0.5f , -0.5f , 
-0.5f , -0.5f , -0.5f , 
-0.5f , -0.5f ,  0.5f , 
-0.5f ,  0.5f ,  0.5f , 
						
 0.5f ,  0.5f ,  0.5f , 
 0.5f ,  0.5f , -0.5f , 
 0.5f , -0.5f , -0.5f , 
 0.5f , -0.5f , -0.5f , 
 0.5f , -0.5f ,  0.5f , 
 0.5f ,  0.5f ,  0.5f , 
						
-0.5f , -0.5f , -0.5f , 
 0.5f , -0.5f , -0.5f , 
 0.5f , -0.5f ,  0.5f , 
 0.5f , -0.5f ,  0.5f , 
-0.5f , -0.5f ,  0.5f , 
-0.5f , -0.5f , -0.5f , 
						
-0.5f ,  0.5f , -0.5f , 
 0.5f ,  0.5f , -0.5f , 
 0.5f ,  0.5f ,  0.5f , 
 0.5f ,  0.5f ,  0.5f , 
-0.5f ,  0.5f ,  0.5f , 
-0.5f ,  0.5f , -0.5f ,  
//NORMALS

0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,

0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,

-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,

1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,

0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,

0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,


//UV Mapping
0.0f, 0.0f,
1.0f, 0.0f,
1.0f, 1.0f,
1.0f, 1.0f,
0.0f, 1.0f,
0.0f, 0.0f,

0.0f, 0.0f,
1.0f, 0.0f,
1.0f, 1.0f,
1.0f, 1.0f,
0.0f, 1.0f,
0.0f, 0.0f,

1.0f, 0.0f,
1.0f, 1.0f,
0.0f, 1.0f,
0.0f, 1.0f,
0.0f, 0.0f,
1.0f, 0.0f,

1.0f, 0.0f,
1.0f, 1.0f,
0.0f, 1.0f,
0.0f, 1.0f,
0.0f, 0.0f,
1.0f, 0.0f,

0.0f, 1.0f,
1.0f, 1.0f,
1.0f, 0.0f,
1.0f, 0.0f,
0.0f, 0.0f,
0.0f, 1.0f,

0.0f, 1.0f,
1.0f, 1.0f,
1.0f, 0.0f,
1.0f, 0.0f,
0.0f, 0.0f,
0.0f, 1.0f,
};

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

	//Model::Cylinder cylinder(1.0f, 3.0f);
	//CUBE_DATA(1.0f, 1.0f, 1.0f)
	VertexBuffer vb(cube, sizeof(cube), false);
	vb.InsertStride<float,36 * 3>(3);
	vb.InsertStride<float,36 * 3>(3);
	vb.InsertStride<float,36 * 2>(2);
	vb.BindData();

	shader.Bind();
	shader.SetUniformMat4("model", glm::mat4(1.0f));
	

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		//Drawing Begins here
		glDrawArrays(GL_TRIANGLES, 0, 36);
		Renderer::Get().curCamera->Shoot();
		Renderer::Get().RenderModels();
		Renderer::Get().curShader->SetUniform3f("lightPos", Renderer::Get().curCameraPos);

		glfwSwapBuffers(window);
	}

}
