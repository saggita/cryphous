#version 330

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragColor;

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	vec3 color1 = texelFetch( texture1, fragCoord, 0 ).rgb * 0.5;
	vec3 color2 = texelFetch( texture2, fragCoord, 0 ).rgb * 0.5;

	fragColor.rgb = color1 + color2;
	fragColor.a = 1.0;
}