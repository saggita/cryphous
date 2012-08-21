#version 150

uniform sampler2D offScreenTexture0;
uniform sampler2D offScreenTexture1;

out vec4 FragColor;

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	FragColor = texelFetch( offScreenTexture0, fragCoord, 0 );//texture( offScreenTexture0, gl_FragCoord.xy / 512.0 );
	FragColor += texelFetch( offScreenTexture1, fragCoord, 0 ); //texture( offScreenTexture1, gl_FragCoord.xy / 512.0 );
}