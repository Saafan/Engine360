#include "Light.h"
#include "Renderer/Renderer.h"

#include "glm/gtc/type_ptr.hpp"

using namespace Light;

int PointLight::numOfPointLights = 0;
int PointLight::numOfSpotLights = 0;
int PointLight::numOfDirectionalLights = 0;


UniformBlock* PointLight::spotLightBlock = nullptr;
UniformBlock* PointLight::pointLightBlock = nullptr;
UniformBlock* PointLight::directionLightBlock = nullptr;


PointLight::PointLight(glm::vec3 lightPosition, Shader* shader)
	: ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)), lightPos(lightPosition)
{
	numOfPointLights++;
	if (!pointLightBlock)
	{
		pointLightBlock = new UniformBlock(SHADER_POINT_LIGHT_BLOCK, SHADER_POINT_LIGHT_BINDING_POINT, shader, false);
		pointLightBlock->InsertData<int>("numOfLights", &numOfPointLights);
	}

	pointLightBlock->InsertData<glm::vec3>("position", glm::value_ptr(lightPos));

	pointLightBlock->InsertData<float>("constant", &constant);
	pointLightBlock->InsertData<float>("linear", &linear);
	pointLightBlock->InsertData<float>("quadratic", &quadratic);

	pointLightBlock->InsertData<glm::vec3>("ambient", glm::value_ptr(ambient));
	pointLightBlock->InsertData<glm::vec3>("diffuse", glm::value_ptr(diffuse));
	pointLightBlock->InsertData<glm::vec3>("specular", glm::value_ptr(specular));

	pointLightBlock->Report();

	pointLightBlock->Bind();
}

PointLight::PointLight()
	: ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)), lightPos(glm::vec3(1.0f))
{

}

DirectionalLight::DirectionalLight(glm::vec3 lightPosition, glm::vec3 lightDirection, Shader* shader)
	: PointLight(), direction(lightDirection)
{
	this->lightPos = lightPosition;
	this->direction = lightDirection;

	numOfDirectionalLights++;
	if (!directionLightBlock)
	{
		directionLightBlock = new UniformBlock(SHADER_DIRECTIONAL_LIGHT_BLOCK, SHADER_DIRECTIONAL_LIGHT_BINDING_POINT, shader, false);
		directionLightBlock->InsertData<int>("numOfLights", &numOfDirectionalLights);
	}

	directionLightBlock->InsertData<glm::vec3>("position", &lightPos);

	directionLightBlock->InsertData<glm::vec3>("ambient", &ambient);
	directionLightBlock->InsertData<glm::vec3>("diffuse", &diffuse);
	directionLightBlock->InsertData<glm::vec3>("specular", &specular);

	directionLightBlock->Bind();
}

SpotLight::SpotLight(glm::vec3 lightPosition, glm::vec3 lightDirection, float innerCutOff, float outerCufOff, Shader* shader)
	: PointLight(lightPosition, shader), direction(lightDirection), innerCutOff(innerCutOff)
{
	if (!spotLightBlock)
		spotLightBlock = new UniformBlock(SHADER_DIRECTIONAL_LIGHT_BLOCK, SHADER_DIRECTIONAL_LIGHT_BINDING_POINT, shader, false);
	SetOuterCutOff(outerCufOff);
	numOfSpotLights++;
}

void DirectionalLight::SetLightDirection(glm::vec3 lightDirection)
{
	this->direction = lightDirection;
}

void PointLight::SetAmbient(glm::vec3 ambientColor)
{
	ambient = ambientColor;
}

void PointLight::SetDiffuse(glm::vec3 diffuseColor)
{
	diffuse = diffuseColor;
}

void PointLight::SetSpecular(glm::vec3 specularColor)
{
	specular = specularColor;
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	this->constant = constant, this->linear = linear, this->quadratic = quadratic;
}

void PointLight::SetConstant(float constant)
{
	this->constant = constant;
}

void PointLight::SetLinear(float linear)
{
	this->linear = linear;
}

void PointLight::SetQuadratic(float quadratic)
{
	this->quadratic = quadratic;
}

void PointLight::SetLightPosition(glm::vec3 lightPosition)
{
	lightPos = lightPosition;
}

void SpotLight::SetLightDirection(glm::vec3 lightDirection)
{
	this->direction = lightDirection;
}

void SpotLight::SetInnerCutOff(float innerCutOff)
{
	if (outerCutOff <= innerCutOff)
		outerCutOff = innerCutOff;

	this->innerCutOff = innerCutOff;
}

void SpotLight::SetOuterCutOff(float outerCutOff)
{
	if (outerCutOff <= innerCutOff)
		innerCutOff = outerCutOff;

	this->outerCutOff = outerCutOff;
}
