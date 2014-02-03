#version 330

uniform sampler2D alphaTexture;
in vec4 color;
out vec4 fragColor;

void main(void)
{
	vec3 N;
	N.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);
	float distance = dot(N.xy, N.xy);
	if (distance > 1.0)
		discard;
	fragColor.rgb = color.rgb;
	fragColor.a = color.a * texture(alphaTexture, gl_PointCoord.xy).a;
}