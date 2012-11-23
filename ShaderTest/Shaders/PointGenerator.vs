#version 330

in vec3 position;
in vec4 color;

out Vertex
{
	vec3 position;
	vec4 color;
} vertex;

void main(void)
{
	vertex.position = position;
	vertex.color = color;
}