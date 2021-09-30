#pragma once
#include "glm/glm.hpp"
#include "Uniform.h"

class Camera {
public:
	Camera();
	void Bind();

	//Calculate and Update View Matrix to Shader
	void Shoot2D();
	void Shoot();

	glm::mat4& GetProjectionMatrix();
	glm::mat4& GetViewMatrix();

private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	double yaw = -90.0, pitch = 0;

	Uniform<glm::mat4>* u_proj = nullptr, * u_view = nullptr;
	Uniform<glm::vec3>* u_cameraPos= nullptr;
};

