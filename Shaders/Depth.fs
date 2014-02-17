#version 150


out vec4 fragColor;
in float dist;

void main(void)
{
	vec3 normal;
	normal.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);
	float distance = dot(normal.xy, normal.xy);
	if (distance >= 1.0) {
		discard;
	}
	normal.z = sqrt( 1.0 - distance );

	fragColor.rgb = vec3( 1.0 / dist + normal.z / 100.0 );// + pointSize * normal.z ); /*dist / 1.0f*/ normalDepth + pointSize * normal.z / 100.0f);
	fragColor.a = 1.0;
}