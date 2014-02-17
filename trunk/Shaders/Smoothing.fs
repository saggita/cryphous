#version 150

uniform sampler2D depthTexture;
uniform int filterRadius;

const float fallOff = 1.0;

out vec4 fragColor;

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	float depth = texelFetch( depthTexture, fragCoord, 0 ).x;
	
	float sum = 0.0;
	float wsum = 0.0;
	
	for( int x= -filterRadius; x<= filterRadius; x+= 1 ) {
		float sampleDepth = texelFetch( depthTexture, fragCoord + x * ivec2(1, 0), 0 ).x;
		
		// spatial domain.
		float r = float(x) * 0.1f;
		float w = exp( -r * r );
		
		// range domain.
		float r2 = (sampleDepth - depth) * fallOff;
		float g = exp(-r2*r2);
		
		sum += sampleDepth * w * g;
		wsum += w * g;
	}
	
	if( wsum > 0.0 ) {
		sum /= wsum;
	}
	
	fragColor.rgb = vec3(sum, sum, sum);
	fragColor.a = 1.0;
}