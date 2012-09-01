#version 330
#extension GL_EXT_gpu_shader4 : enable

layout(points) in;
layout(points, max_vertices = 1) out;

in Vertex
{
	vec3 position;
	vec4 color;
	vec3 normal;
} vertex[];

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform float pointSize;
uniform sampler2D noiseTexture;
uniform int repetitionLevel;
uniform float particleDiameter;
out vec4 color;
 
void main() {
  for( int i = 0; i < gl_in.length(); i++){
    int howMany = int(vertex[i].color.a * 1.0);
	float random = texelFetch2D( noiseTexture, ivec2( int(mod(gl_PrimitiveIDIn, 100)), repetitionLevel ), 0 ).a;
	float over = mod( vertex[i].color.a * 1.0, 1.0 );
	if( over > random ) {
		++howMany;
	}
	for( int j = 0; j < howMany; j++) {
		vec3 noiseVector = texelFetch2D( noiseTexture, ivec2(j,repetitionLevel), 0 ).rgb - vec3( 0.5, 0.5, 0.5);
		noiseVector *= particleDiameter;
		vec3 position = vertex[i].position + noiseVector;
		gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );
		float dist = length(gl_Position);
		gl_PointSize = pointSize / dist;
		color = vertex[i].color;
		color.rgb = vertex[i].normal + normalize( noiseVector );
		EmitVertex();
	}
	EndPrimitive();
  }
}
