#version 330
#extension GL_EXT_gpu_shader4 : enable

layout(points) in;
layout(points, max_vertices = 1) out;

in Vertex
{
	vec3 position;
	vec4 color;
} vertex[];

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;
uniform int repeatLevel;
out vec4 color;
 
void main() {
  for( int i = 0; i < gl_in.length(); i++){
	gl_Position = projectionMatrix * modelviewMatrix * vec4( vertex[i].position + vec3( 1.0 * repeatLevel, 0.0, 0.0), 1.0 );
	float dist = length(gl_Position);
	gl_PointSize = pointSize / dist;
	color = vertex[i].color;
	if( repeatLevel == 10 ) {
		color.r += 0.1 * repeatLevel;
	}
	EmitVertex();
	EndPrimitive();
  }
}
