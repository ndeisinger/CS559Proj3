#version 400
#extension GL_ARB_gpu_shader5 : require
#extension GL_ARB_shader_subroutine : require

subroutine void renderPassType();
subroutine uniform renderPassType renderPass;

layout (location = 0) out vec4 fragColor;

in vec3 vert_position;
in vec3 normal;
in vec2 texCoord;
in vec4 shadowCoord;

//Information on the light
uniform	vec4 position;
uniform	vec3 color;
uniform	vec3 amb;
uniform	vec3 diff;
uniform	vec3 spec;

//Information on the material
uniform	vec3 kA;
uniform	vec3 kD;
uniform	vec3 kS;
uniform	float shininess;

uniform sampler2D Tex1;
uniform sampler2DShadow shadow_map;
uniform bool shadow_pass;
uniform bool draw_shadows;

vec3 phong_ds()
{
	vec3 n = normalize(normal); 
	vec3 s = normalize(vec3(position) - vert_position);
	vec3 v = normalize(vec3(-vert_position));
	vec3 r = reflect(-s, n);
	float sDotNorm = max(dot(s, n), 0.0);
	vec3 diff_comp = diff * kD * sDotNorm;
	vec3 spec_comp = vec3(0.0);
	if (sDotNorm > 0.0 )
	{
		spec_comp = spec * kS * pow(max(dot(r, v), 0.0), shininess);
	}
	return diff_comp + spec_comp;
}

void shade()
{
	//Do the actual shading calculation
	vec4 texColor = texture(Tex1, texCoord);
	vec3 amb_comp = amb * kA;
	float shadow = textureProj(shadow_map, shadowCoord);
	if (shadow > 0)
	{
		//Not in shadow
		vec3 ds_result = phong_ds();
		fragColor = texColor *  vec4((amb_comp + ds_result), 1.0);
	}
	else
	{
		fragColor = vec4(0.0, 0.0, 0.0, 1.0);
		//fragColor = texColor *  vec4(amb_comp, 1.0);
	}
}

void recordDepth()
{
	//Do no lighting calcs - just getting the depths
}

void main()
{
/*
	if (shadow_pass) 
	{
		//Nothing to do here
	}*/
	if (draw_shadows)
	{
		//Do calculations for a shadow
		shade();
	}
	else
	{
		//Do standard ADS
		
		vec4 texColor = texture(Tex1, texCoord);
		vec3 amb_comp = amb * kA;
		vec3 ds_result = phong_ds();
		fragColor = texColor *  vec4((amb_comp + ds_result), 1.0);
	}
}