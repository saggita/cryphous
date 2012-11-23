#version 330

uniform sampler2D alphaTexture;
in vec4 color;
out vec4 fragColor;

void main(void)
{
	fragColor.rgb = color.rgb;
	fragColor.a = color.a * texture(alphaTexture, gl_PointCoord.xy).a;
}