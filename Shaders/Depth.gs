#version 330
#extension GL_EXT_gpu_shader4 : enable

layout(points) in;
layout(points, max_vertices = 1) out;

in Vertex
{
	vec3 position;
	float density;
} vertex[];

out vec3 eyePosition;
out float dist;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;

void main() {
  for( int i = 0; i < gl_in.length(); i++){
    vec3 position = vertex[i].position;
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	dist = length(gl_Position);
	bool isIsolated = (vertex[i].density < 800.0);
	gl_PointSize = isIsolated ? (pointSize / dist * 0.25) : (pointSize/dist);
	eyePosition = (modelviewMatrix * vec4(position, 1.0)).xyz;
	EmitVertex();
	EndPrimitive();
  } 
}
