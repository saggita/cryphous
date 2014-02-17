#version 150

in vec4 vertColor;
out vec4 fragColor;
uniform float pointSize;

void main(void)
{
	vec3 normal;
	normal.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);
	float distance = dot(normal.xy, normal.xy);
	if (distance > 1.0) {
		discard;
	}
	normal.z = sqrt( 1.0 - distance );
	
	fragColor.rgb = vertColor.rgb;
	fragColor.a = 1.0;
}