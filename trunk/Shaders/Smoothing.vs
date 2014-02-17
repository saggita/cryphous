#version 150

in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
}