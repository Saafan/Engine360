#include "Camera.h"
#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"
#include "gtc/matrix_transform.hpp"

glm::dvec3 dir;
glm::dvec3& cameraPos = Renderer::Get().curCameraPos;

glm::vec2 GetDeltaMouse()
{

	double* newX = &(Renderer::Get().x);
	double* newY = &(Renderer::Get().y);
	double oldX = *newX, oldY = *newY;
	glfwGetCursorPos(Renderer::Get().window, newX, newY);

	static bool first = true;
	if (first)
	{
		first = false;
		return glm::vec2(0.0f);
	}
	return glm::vec2((*newX - oldX), (*newY - oldY));
}

void Camera::Bind()
{
	proj = glm::perspective(glm::radians(60.0f), (float)WIDTH / (float)HEIGHT, 0.0001f, 1000.0f);
	Renderer::Get().curShader->SetUniformMat4(SHADER_PROJ, proj);
	Renderer::Get().curCamera = this;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glm::dvec3 cameraCross = glm::cross(dir, glm::dvec3(0.0f, 1.0f, 0.0f));

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		cameraPos -= cameraCross * CAMERA_MOTION_SPEED;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		cameraPos += cameraCross * CAMERA_MOTION_SPEED;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		cameraPos += dir * CAMERA_MOTION_SPEED;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		cameraPos -= dir * CAMERA_MOTION_SPEED;
}

void Camera::Shoot2D()
{
	glm::mat4 ortho = glm::ortho(0.01f, (float)WIDTH, 0.01f, (float)HEIGHT, 0.001f, 1000.0f);
	glm::mat4 view(1.0f);

	Renderer::Get().UpdateCameraPosition();
	Renderer::Get().curShader->SetUniformMat4(SHADER_PROJ, ortho);
	Renderer::Get().curShader->SetUniformMat4(SHADER_VIEW, view);
}

void Camera::Shoot()
{
	glm::vec2 delt = GetDeltaMouse();

	yaw += delt.x * CAMERA_SPEED;
	pitch -= delt.y * CAMERA_SPEED;

	dir.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	dir.y = glm::sin(glm::radians(pitch));
	dir.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	dir = glm::normalize(dir);


	glfwSetKeyCallback(Renderer::Get().window, key_callback);

	view = glm::lookAt(cameraPos, cameraPos + dir, glm::dvec3(0.0f, 1.0f, 0.0f));

	Renderer::Get().UpdateCameraPosition();

	Renderer::Get().curShader->SetUniformMat4(SHADER_VIEW, view);
}

void Camera::UpdateViewProjectionMatrix()
{
	Renderer::Get().curShader->SetUniformMat4(SHADER_PROJ, proj);
	Renderer::Get().curShader->SetUniformMat4(SHADER_VIEW, view);
}

glm::mat4& Camera::GetProjectionMatrix()
{
	return proj;
}

glm::mat4& Camera::GetViewMatrix()
{
	return view;
}
