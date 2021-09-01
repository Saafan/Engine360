#version 330 core

layout(location = 0) vec3 pos;
layout(location = 1) vec3 normal;
layout(location = 2) vec2 tex;

out vec3 u_pos;

void main()
{
	gl_Position = vec4(pos,1.0);
	u_pos = pos;
}


#fragment

out vec4 color;

void main()
{
	color = vec4(0.5, 0.0 ,1.0, 1.0);
}