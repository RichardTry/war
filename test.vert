#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexCol;

out vec3 colr;

uniform mat4 mvp;

void main()
{
	colr = vertexCol;
	gl_Position = mvp * vec4(vertexPos, 1.0);
}
