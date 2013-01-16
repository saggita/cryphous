#version 150

uniform sampler2D offScreenTexture;
uniform sampler2D pointSpriteTexture;

out vec4 FragColor;

void main(void)
{
	FragColor = texelFetch( offScreenTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0 ); //* 0.125;
	//FragColor += texelFetch( pointSpriteTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0 ) * 0.5;
}
