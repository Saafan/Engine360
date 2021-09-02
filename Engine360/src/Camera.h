#pragma once
#include "glm.hpp"


class Camera {
public:
	void Bind();
	void CalculateViewMatrix();
	
private:
	glm::mat4 view;
	double yaw = -90.0, pitch = 0;
	
};

