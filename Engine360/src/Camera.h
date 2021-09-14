#pragma once
#include "glm.hpp"


class Camera {
public:
	void Bind();

	//Calculate and Update View Matrix to Shader
	void Shoot2D();
	void Shoot();

	
private:
	glm::mat4 view;
	double yaw = -90.0, pitch = 0;
	
};

