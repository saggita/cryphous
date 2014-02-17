#version 150

uniform sampler2D normalTexture;
uniform sampler2D thicknessTexture;
uniform sampler2D backgroundTexture;
uniform vec3 eyePosition;
uniform vec3 fluidColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform float alpha;

uniform vec3 lightPos;

out vec4 fragColor;

vec3 getDiffuseColor(ivec2 fragCoord, vec3 normal)
{
	vec3 lightDirection = normalize( -lightPos.xyz );
	
	float diffuse = dot( normal, lightDirection ) * 0.5 + 0.5;
	
	return diffuse * diffuseColor;
}

vec3 getAbsoptionColor(ivec2 fragCoord)
{	
	float thickness = texelFetch( thicknessTexture, fragCoord, 0 ).r * 1.0;
	vec3 absorb = vec3( exp(-thickness * 0.1) );

	return absorb * fluidColor;
}

vec3 getRefractionColor( ivec2 fragCoord, vec3 normal )
{
	float thickness = texelFetch( thicknessTexture, fragCoord, 0 ).r;
	
	float refraction = 10.0 * ( 1.0 - thickness );// * 0.03;
	ivec2 refractFrag = ivec2( normal.x * refraction, normal.y * refraction );
	vec3 refractColor = texelFetch( backgroundTexture, fragCoord.xy + refractFrag, 0).rgb;
	
	return refractColor;
}

vec3 getSpecularColor( ivec2 fragCoord, vec3 normal )
{
	vec3 lightDirection = normalize( -lightPos.xyz );
	
	vec3 half = normalize( lightDirection + normalize(-eyePosition) );
	float specular = pow( max( 0.0, dot( normal, half ) ), 1 );

	return specular * specularColor;
}

void main(void)
{
	ivec2 fragCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	vec3 backgroundColor = texelFetch( backgroundTexture, fragCoord, 0).rgb;
	
	vec3 normal = texelFetch( normalTexture, fragCoord, 0).rgb;
	
	if( abs( normal ) == 0.0f ) {
		fragColor.rgb = backgroundColor;
		fragColor.a = 1.0;
		return;
	}

	normal = normalize( normal );

	vec3 diffuse = getDiffuseColor( fragCoord, normal );
	vec3 specular = getSpecularColor( fragCoord, normal );
	vec3 absorption = getAbsoptionColor( fragCoord );
	vec3 refraction = getRefractionColor( fragCoord, normal );
	float thickness = ( 1.0 -texelFetch( thicknessTexture, fragCoord, 0 ).r );
	thickness *= alpha;
	
	vec3 color = diffuse + specular + absorption;
	fragColor.rgb = mix( color, refraction, thickness);
	fragColor.a = thickness;
}
	
