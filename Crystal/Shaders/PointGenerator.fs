#version 330

uniform int maxLevel;
uniform sampler2D alphaTexture;
uniform float alphaThreshold;
//uniform sampler2D depthTexture;
in vec4 color;
out vec4 fragColor;
in vec3 normal;
in vec4 lightPos;

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main(void)
{
	float alpha = color.a * texture(alphaTexture, gl_PointCoord.xy).a;
	if( alpha < alphaThreshold ) {
		discard;
	}
	fragColor = color;

	vec3 light = normalize( lightPos.xyz - gl_FragCoord.xyz );
	float diffuse = dot( light, normal );

	fragColor.rgb = vec3( 0.5, 0.5, 0.75 );
	if( diffuse > 0.0 ) {
		vec3 view = normalize( gl_FragCoord.xyz );
		vec3 halfway = normalize( light - view );
		float specular = pow(max(dot(normal, halfway),0.0), 10.0);
		fragColor.rgb += vec3(diffuse * 0.5, diffuse * 0.5, diffuse * 0.5) + vec3( specular, specular, specular);
	}
}