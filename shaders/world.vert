#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexCol;

out vec3 pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	pos = vertexPos;
	gl_Position = projection * view * model * vec4(vertexPos, 1.0);
}