#version 330

uniform sampler2D depthTexture;
uniform sampler2D thicknessTexture;
uniform float far;
uniform float near;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

const vec3 fluidColor = vec3( 0.5, 0.5, 1.0 );
const vec3 specularColor = vec3( 1.0, 1.0, 1.0 );

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
	float depth = texelFetch( depthTexture, fragCoord, 0 ).r;

	if( depth < 1.0e-5 ) {
		discard;
		return;
	}
	
	vec3 eyePosition = uvToEye( fragCoord, depth );
	
	ivec2 texCoord1 = ivec2( fragCoord.x + 1, fragCoord.y );
	ivec2 texCoord2 = ivec2( fragCoord.x - 1, fragCoord.y );
	
	vec3 ddx = uvToEye( texCoord1, texelFetch( depthTexture, texCoord1, 0).x ) - eyePosition;
	vec3 ddx2 = eyePosition - uvToEye(texCoord2, texelFetch( depthTexture, texCoord2, 0).x);
	if( abs(ddx.z) > abs( ddx2.z ) ) {
		ddx = ddx2;
	}
	
	texCoord1 = ivec2( fragCoord.x, fragCoord.y + 1 );
	texCoord2 = ivec2( fragCoord.x, fragCoord.y - 1 );
	
	vec3 ddy = uvToEye(texCoord1, texelFetch( depthTexture, texCoord1, 0).x ) - eyePosition;
	vec3 ddy2 = eyePosition - uvToEye( texCoord2, texelFetch( depthTexture, texCoord2, 0).x);
	if( abs(ddy.z) > abs( ddy2.z ) ) {
		ddy = ddy2;
	}
	
	vec3 normal = cross( ddx, ddy );
	normal = normalize( normal );

	vec3 lightDirection = vec3( 1.0, 1.0, 1.0 );
	lightDirection = normalize( lightDirection );
	
	float diffuse = dot( normal, lightDirection ) * 0.5 + 0.5;
	
	vec3 half = normalize( lightDirection + normalize(-eyePosition) );
	float specular = pow( max( 0.0, dot( normal, half)), 10.0 );

	float thickness = texelFetch( thicknessTexture, fragCoord, 0 ).r;
	vec3 absorb = vec3( exp(-thickness*0.2) );
	
	fragColor.rgb = diffuse * specular * specularColor + absorb * fluidColor;
	fragColor.a = thickness;
}
	
