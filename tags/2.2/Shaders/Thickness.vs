#version 330

in vec3 position;
in float density;

out Vertex
{
	vec3 position;
	float density;
} vertex;

void main(void)
{
	vertex.position = position;
	vertex.density = density;
}