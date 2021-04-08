#version 330 core

in vec3 colr;
out vec3 color;

void main()
{
	color = colr;
	//color = vec3(1.0f, 0.5f, 0.2f);
}
