#version 330
 
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec2 texCoord;
in Vertex
{
	vec2 texCoord;
} vertex[];

void main() {
  for(int i = 0; i < gl_in.length(); i++) {
    gl_Position = gl_in[i].gl_Position;
	texCoord = vertex[i].texCoord;
	EmitVertex();
  }
  EndPrimitive();
}
