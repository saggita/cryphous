#version 150

in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

uniform vec3 lightPos;
//out vec4 lightPosition;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	//lightPosition = projectionMatrix * modelviewMatrix * vec4( lightPos, 1.0 );
}