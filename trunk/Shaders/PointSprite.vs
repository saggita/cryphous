#version 330

in vec3 position;

out Vertex
{
	vec3 position;
} vertex;

void main(void)
{
	vertex.position = position;
}