#pragma once
#include "Uniform.h"
#include "glm/fwd.hpp"

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
	glm::mat4* view;
	glm::mat4* proj;
	double yaw = -90.0, pitch = 0.0;

	Uniform<glm::mat4>* u_proj = nullptr, * u_view = nullptr;
	Uniform<glm::vec3>* u_cameraPos= nullptr;
};

