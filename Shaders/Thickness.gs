#version 330
#extension GL_EXT_gpu_shader4 : enable

layout(points) in;
layout(points, max_vertices = 1) out;

in Vertex
{
	vec3 position;
	float density;
} vertex[];

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;
 
void main() {
  for( int i = 0; i < gl_in.length(); i++){
	vec3 position = vertex[i].position;
	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
	float dist = length(gl_Position);
	bool isIsolated = (vertex[i].density < 800.0);
	gl_PointSize = isIsolated ? (pointSize / dist * 0.25) : (pointSize/dist);
	EmitVertex();
	EndPrimitive();
	}

/*		for( int j = 0; j < 3; ++j ) {
			vec3 position = vertex[i].position;
			position.x += 1.0 * j;
			gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
			float dist = length(gl_Position);
			gl_PointSize = pointSize / dist;
			EmitVertex();
			EndPrimitive();
		}*/
}
