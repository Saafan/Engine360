#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

out vec4 i_pos;
out vec3 i_normal;
out vec2 i_tex;

uniform mat4 model;

layout(std140) uniform Matrices
{
	mat4 proj;
	mat4 view;
};

void main()
{
	mat4 mvp = proj * view * model;
	gl_Position = mvp * vec4(pos, 1.0);
	i_pos = model * vec4(pos, 1.0);
	i_normal = mat3(transpose(inverse(model))) * normal;

	i_tex = tex;
}

#fragment
#version 330 core

struct Material {
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;

	sampler2D ambientTex;
	sampler2D diffuseTex;
	sampler2D specularTex;

	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


layout(std140) uniform pointLightsBlock
{
	int numOfPointLights;
	PointLight pointLights[MAX_NR_LIGHTS];
};

layout(std140) uniform dirLightsBlock
{
	int numOfDirectionalLight;
	DirLight dirLights[MAX_NR_LIGHTS];
};

layout(std140) uniform spotLightBlock
{
	int numOfSpotLight;
	SpotLight spotLights[MAX_NR_LIGHTS];
};

out vec4 color;

in vec4 i_pos;
in vec3 i_normal;
in vec2 i_tex;

uniform vec3 cameraPos;

uniform sampler2D textureSlot;

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int SPECULAR_EXPONENT = 32;
uniform vec4 colorOut;

void main()
{
	vec4 ambientColor = texture(textureSlot, i_tex);

	float diffuse = max(dot(normalize(i_normal), normalize(pointLights[0].position - i_pos.xyz)), 0);
	vec4 diffMap = diffuse * texture(textureSlot, i_tex);
	float specular = pow(max(dot(normalize(cameraPos - i_pos.xyz), normalize(reflect(-(pointLights[0].position - i_pos.xyz), i_normal))), 0), SPECULAR_EXPONENT);
	vec4 specMap = specular * texture(textureSlot, i_tex);
	vec4 result = (specMap + diffMap + ambientColor);
	color = result;
}