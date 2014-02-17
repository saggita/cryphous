#version 150

uniform sampler2D depthTexture;
uniform float far;
uniform float near;
uniform int width;
uniform int height;

out vec4 fragColor;

vec3 uvToEye(vec2 texCoord, float z)
{
	texCoord.x /= width;
	texCoord.y /= height;
	vec2 xy = texCoord * 2.0 - 1.0;
	float a = far / ( far - near );
	float b = far * near / ( near - far );
	return vec3( xy, -1.0 ) * b / ( z - a );
}

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);

	float depth = texelFetch( depthTexture, fragCoord, 0 ).r;

	if( depth < 1.0e-5 ) {
		//discard;
		fragColor.rgb = vec3( 0.0, 0.0, 0.0 );
		fragColor.a = 1.0;
		return;
	}

	vec3 position = uvToEye( gl_FragCoord.xy, depth);
	
	fragColor = vec4( normalize( cross( dFdx( position.xyz ), dFdy( position.xyz ) ) ), 1.0f);
}