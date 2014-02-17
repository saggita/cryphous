#version 150

in vec3 position;
in float density;

out float dist;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	dist = length( gl_Position );
	gl_PointSize = pointSize / dist;
}