#include "Camera.h"
#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"

glm::vec2& GetDeltaMouse()
{
	double* oldx = &(Renderer::Get().x);
	double* oldy = &(Renderer::Get().y);
	glfwGetCursorPos(Renderer::Get().window, oldx, oldy);

}

void Camera::Bind()
{
	Renderer::Get().curCamera = this;
}

void Camera::CalculateViewMatrix()
{
		
}