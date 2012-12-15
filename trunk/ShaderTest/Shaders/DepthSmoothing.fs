#version 330

uniform sampler2D depthTexture;
const vec2 smoothScale = vec2(2.0, 2.0);
const float fallOff = 2.0;

out vec4 fragColor;

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	float depth = texelFetch( depthTexture, fragCoord, 0 ).a;
	
	float filterRadius = 1.0;
	
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
	}
	
	fragColor = vec4(sum, sum, sum, 1.0);
}