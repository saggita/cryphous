#version 150

in vec3 position;
in vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;

out vec4 vertColor;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	float dist = length( gl_Position );
	gl_PointSize = pointSize / dist;
	vertColor = color;
}