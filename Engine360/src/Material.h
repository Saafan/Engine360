#pragma once

#include "glm/glm.hpp"
#include "Texture.h"

class Material
{
public:
	Material();
	Material(glm::vec3 ambientColor);
	Material(Texture& diffuseTexture);

	void SetAmbient(glm::vec3 color);

	void SetDiffuse(glm::vec3 color);
	void SetDiffuse(Texture& texture);

	void SetSpecular(glm::vec3 color);
	void SetSpecular(Texture& texture);

	void SetShininess(float shininess);
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Texture* diffuseTex = nullptr;
	Texture* specularTex = nullptr;

	float shininess = 0.0f;
};
