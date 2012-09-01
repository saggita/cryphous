#version 330

in vec3 position;
in vec4 color;
in vec3 normal;

out Vertex
{
	vec3 position;
	vec4 color;
	vec3 normal;
} vertex;

void main(void)
{
	vertex.position = position;
	vertex.color = color;
	vertex.normal = normal;
}