#version 330
#extension GL_EXT_gpu_shader4 : enable
 
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
 
in Vertex
{
	vec3 position;
} vertex[];

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main() {
  for(int i = 0; i < gl_in.length(); i++) {
    gl_Position = projectionMatrix * modelviewMatrix * vec4(vertex[i].position, 1.0);
    EmitVertex();
  }
  EndPrimitive();
}