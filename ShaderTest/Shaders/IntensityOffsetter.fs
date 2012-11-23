#version 150

uniform sampler2D offScreenTexture;
uniform vec3 colorOffset;
uniform float intensityScale;

out vec4 FragColor;

void main(void)
{
	FragColor = texelFetch( offScreenTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0 );
	FragColor.rgb += colorOffset;
	FragColor.rgb *= intensityScale;
}
