#version 330

in vec2 texCoord;
out vec4 FragColor;
uniform sampler2D textureObject;
uniform float intensity;
uniform int useTexture;

void main(void)
{
	if( useTexture == 1 ) {
		FragColor = texture(textureObject, texCoord) * intensity;
	}
	else {
		FragColor = vec4( intensity );
	}
}
