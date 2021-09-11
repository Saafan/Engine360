#version 330 core

layout(location = 0) in vec3 pos;
//layout(location = 1) in vec3 normal;
//layout(location = 2) in vec2 tex;

out vec4 u_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	mat4 mvp =  proj * view * model;
	gl_Position = mvp * vec4(pos,1.0);
}


#fragment
#version 330 core

out vec4 color;

uniform vec3 cameraPos;

void main()
{
	color = vec4(0.5, 0.0, 0.5, 1.0);
}