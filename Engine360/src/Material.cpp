#include "Material.h"

Material::Material() : ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f))
{

}

Material::Material(glm::vec3 ambientColor) : Material()
{
	ambient = ambientColor;
}

Material::Material(Texture& diffuseTexture) : Material()
{
	diffuseTex = &diffuseTexture;
}

void Material::SetAmbient(glm::vec3 color)
{
	ambient = color;
}

void Material::SetDiffuse(glm::vec3 color)
{
	diffuse = color;
}

void Material::SetDiffuse(Texture& texture)
{
	diffuseTex = &texture;
}

void Material::SetSpecular(glm::vec3 color)
{
	specular = color;
}

void Material::SetSpecular(Texture& texture)
{
	specularTex = &texture;
}

void Material::SetShininess(float shininess)
{
	this->shininess = shininess;
}
