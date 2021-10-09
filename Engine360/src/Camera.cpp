#include "glm/glm.hpp"
#include "Camera.h"
#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"

#include "glm/gtc/matrix_transform.hpp"
#include "UniformBlock.h"

glm::vec3 dir;
glm::vec3& cameraPos = *(Renderer::Get().curCameraPos);

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

Camera::Camera() : view(glm::mat4(1.0f)), proj(glm::mat4(1.0f))
{
	uniformCameraPos = new Uniform<glm::vec3>(SHADER_CAMERA_POS, cameraPos, Renderer::Get().curShader);
	viewProjBlock = new UniformBlock("Matrices", 0, nullptr, false);
	viewProjBlock->InsertData<glm::mat4>("proj", glm::value_ptr(proj));
	viewProjBlock->InsertData<glm::mat4>("view", glm::value_ptr(view));


	viewProjBlock->Bind();
}

void Camera::Bind()
{
	proj = glm::perspective(glm::radians(60.0f), (float)WIDTH / (float)HEIGHT, 0.0001f, 1000.0f);
	Renderer::Get().curCamera = this;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glm::vec3 cameraCross = glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f));

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
}

void Camera::Shoot()
{
	glm::vec2 delt = GetDeltaMouse();

	yaw += delt.x * (double)CAMERA_SPEED;
	pitch -= delt.y * (double)CAMERA_SPEED;

	dir.x = glm::cos((float)glm::radians(yaw)) * (float)glm::cos(glm::radians(pitch));
	dir.y = glm::sin((float)glm::radians(pitch));
	dir.z = glm::sin((float)glm::radians(yaw)) * (float)glm::cos(glm::radians(pitch));
	dir = glm::normalize(dir);

	glfwSetKeyCallback(Renderer::Get().window, key_callback);

	view = glm::lookAt(cameraPos, cameraPos + dir, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4& Camera::GetProjectionMatrix()
{
	return proj;
}

glm::mat4& Camera::GetViewMatrix()
{
	return view;
}