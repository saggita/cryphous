#version 150

in vec4 vertColor;
out vec4 fragColor;

void main(void)
{
	fragColor.rgba = vertColor;//vec4( 1.0, 1.0, 1.0, 1.0 );
}
