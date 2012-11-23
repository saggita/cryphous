#version 330

in vec2 texCoord;
out vec4 FragColor;
uniform sampler2D textureObject;
uniform float intensityScale;

void main(void)
{
	float texel = texture(textureObject, texCoord).a;
	texel *= intensityScale;
	FragColor = vec4(texel, texel, texel, 0.0);
}
