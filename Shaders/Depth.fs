#version 330

uniform mat4 projectionMatrix;

in vec3 eyePosition;
out vec4 fragColor;
uniform float pointSize;
in float dist;

void main(void)
{
	vec3 normal;
	normal.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);
	float distance = dot(normal.xy, normal.xy);
	if (distance > 0.99) {
		discard;
	}
	normal.z = sqrt( 1.0 - distance );

	vec4 sphereEyePosition = vec4( eyePosition + normal * pointSize, 1.0 );

	vec4 clipSpacePosition = projectionMatrix * sphereEyePosition;

	float normalDepth = (clipSpacePosition.z / clipSpacePosition.w) * 0.5 + 0.5;

	fragColor.rgb = vec3( dist / 100.0f + normal.z / 100.0f);//normalDepth);
	fragColor.a = 0.5;
}