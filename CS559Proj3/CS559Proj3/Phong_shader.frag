#version 400
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 fragColor;

in vec3 vert_position;
in vec3 normal;
in vec3 vert_color;

uniform lightInfo {
	vec4 position;
	vec3 color;
	vec3 amb;
	vec3 diff;
	vec3 spec;
	int spec_exp; //TODO: Have this here or in other location?
};

uniform materialInfo {
	vec3 kA;
	vec3 kD;
	vec3 kS;
	float shininess;
};

//Once more, in the final we can stuff down this stuff via a material struct.
void main()
{

	vec3 n = normalize(normal); 
	vec3 s = normalize(vec3(position) - vert_position);
	vec3 v = normalize(vec3(-vert_position));
	vec3 r = reflect(-s, n);
	vec3 amb_comp = amb * kA;
	float sDotNorm = max(dot(s, n), 0.0);
	vec3 diff_comp = diff * kD * sDotNorm;
	vec3 spec_comp = vec3(0.0);
	if (sDotNorm > 0.0 )
	{
		spec_comp = spec * kS * pow(max(dot(r, v), 0.0), shininess);
	}
	fragColor = vec4(vert_color * (amb_comp + diff_comp) + spec_comp, 1.0);
}