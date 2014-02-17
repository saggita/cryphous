#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;

in vec3 position;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	float dist = length( gl_Position );
	gl_PointSize = ( pointSize / dist );
}