#pragma once

#include "glm/glm.hpp"
#include "UniformBlock.h"

class Shader;

namespace Light
{
	class PointLight
	{
	public:
		PointLight(glm::vec3 lightPosition, Shader* shader = nullptr);
		PointLight();

		void SetAmbient(glm::vec3 ambientColor);
		void SetDiffuse(glm::vec3 diffuseColor);
		void SetSpecular(glm::vec3 specularColor);

		void SetAttenuation(float constant, float linear, float quadratic);
		void SetConstant(float constant);
		void SetLinear(float linear);
		void SetQuadratic(float quadratic);

	protected:
		static UniformBlock* pointLightBlock;
		static UniformBlock* spotLightBlock;
		static UniformBlock* directionLightBlock;

		static int numOfPointLights;
		static int numOfSpotLights;
		static int numOfDirectionalLights;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;

		glm::vec3 lightPos;

		void SetLightPosition(glm::vec3 lightPosition);
	};

	class SpotLight : public PointLight
	{
	public:
		SpotLight(glm::vec3 lightPosition, glm::vec3 lightDirection, float innerCutOff = 40.0f, float outerCufOff = 60.0f,Shader* shader = nullptr);
		void SetLightDirection(glm::vec3 lightDirection);
		void SetInnerCutOff(float innerCutOff);
		void SetOuterCutOff(float outerCutOff);
	private:
		glm::vec3 direction;

		float innerCutOff = 40.0f;
		float outerCutOff = 60.0f;
	};


	class DirectionalLight : public PointLight
	{
	public:
		DirectionalLight(glm::vec3 lightPosition, glm::vec3 lightDirection, Shader* shader = nullptr);
		void SetLightDirection(glm::vec3 lightDirection);
	private:
		glm::vec3 direction;
	};
}