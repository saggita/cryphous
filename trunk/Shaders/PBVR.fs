#version 330

in vec4 color;
out vec4 fragColor;
uniform float pointSize;

void main(void)
{
	vec3 normal;
	normal.xy = gl_PointCoord.xy * vec2(2.0, -2.0) + vec2(-1.0, 1.0);
	float distance = dot(normal.xy, normal.xy);
	if (distance > 1.0) {
		discard;
	}
	normal.z = sqrt( 1.0 - distance );
	
	vec3 lightDirection = vec3(1.0, 1.0, 1.0);
	normalize( lightDirection );

	float diffuse = dot( normal, lightDirection ) * 0.5 + 0.5;

	fragColor.rgb = color.rgb * diffuse;
	//float alpha = exp(-distance*2.0);
	//fragColor.a = 0.1;

	
	//vec3 half = normalize( lightDirection + normalize(-eyePosition) );
	//float specular = pow( max( 0.0, dot( normal, half)), 10.0 );
}