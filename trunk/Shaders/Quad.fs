#version 150

uniform sampler2D offScreenTexture;

out vec4 FragColor;

void main(void)
{
	FragColor = texelFetch( offScreenTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0 );
}
