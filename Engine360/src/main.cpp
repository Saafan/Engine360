#include "Renderer/Renderer.h"

#include <iostream>

int main()
{
    GLFWwindow* window = Renderer::Get().window;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Engine360", nullptr, nullptr);

    if (glewInit() != GLEW_OK)
        std::cout << "Initialization of GLEW Failed!" << std::endl;
    

    if (!glfwInit())
        std::cout << "Initialization of GLFW Failed!" << std::endl;

    glfwMakeContextCurrent(window);


    while (!glfwWindowShouldClose(window))
    {

    }


}
