#version 330

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
in vec3 position;
in vec2 texCoord;

out Vertex
{
	vec2 texCoord;
} vertex;

void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vertex.texCoord = texCoord;
}