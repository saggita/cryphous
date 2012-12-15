#version 330

uniform sampler2D depthTexture;
uniform float far;
uniform float near;

out vec4 fragColor;

vec3 uvToEye(vec2 texCoord, float z)
{
	vec2 xy = texCoord * 2.0 - 1.0;
	float a = far / ( far - near );
	float b = far * near / ( near - far );
	return vec3( xy, -1.0 ) * b / ( z - a );
}

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	float depth = texelFetch( depthTexture, fragCoord, 0 ).a;
	
	vec3 eyePosition = uvToEye( fragCoord, depth );
	
	vec2 texCoord1 = vec2( fragCoord.x + texelSize, fragCoord.y );
	vec2 texCoord2 = vec2( fragCoord.x - texelSize, fragCoord.y );
	
	vec3 ddx = uvToEye( texCoord1, texelFetch( depthTexture, texCoord1).x ) - eyePos;
	vec3 ddx2 = eyePos - uvToEye(texCoord2, textelFetch( depthTexture, texCoord2).x);
	if( abs(ddx.z) > abs( ddx2.z ) {
		ddx = ddx2;
	}
	
	/*float filterRadius = 1.0;
	
	float sum = 0.0;
	float wsum = 0.0;
	
	for( float x= -filterRadius; x<= filterRadius; x+= 1.0 ) {
		float sampleDepth = texelFetch( depthTexture, fragCoord + x * smoothScale ).x;
		
		// spatial domain.
		float r = x * smoothScale;
		float w = exp(-r*r);
		
		// range domain.
		float r2 = (sampleDepth - depth) * fallOff;
		float g = exp(-r2*r2);
		
		sum = += sampleDepth * w * g;
		wsum += w * g;
	}
	
	if( wsum > 0.0 ) {
		sum /= wsum;
	}*/
}
	
