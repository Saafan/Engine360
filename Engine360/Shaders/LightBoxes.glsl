#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vPosition;
}

#shader fragment
#version 330 core

out vec4 color;

uniform vec3 lightColor;

void main()
{
	color = vec4(lightColor, 1.0f);
}