#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
in vec3 position;
in vec4 color;

out vec4 vertColor;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vertColor = color;
}