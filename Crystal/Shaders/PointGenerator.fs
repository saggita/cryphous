#version 330

uniform int maxLevel;
uniform sampler2D alphaTexture;
uniform float alphaThreshold;
//uniform sampler2D depthTexture;
in vec4 color;
out vec4 fragColor;

void main(void)
{
	float alpha = color.a * texture(alphaTexture, gl_PointCoord.xy).a;
	if( alpha < alphaThreshold ) {
		discard;
	}
	fragColor = color / float(maxLevel);
	//if( gl_FragDepth < texture(depthTexture, gl_FragCoord.xy).r ) {
	//	fragColor = vec4( gl_FragCoord.x, gl_FragCoord.y, 0.0, 1.0 );
	//}
}