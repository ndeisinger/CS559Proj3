#version 400
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 fragColor;

in vec3 vert_position;
in vec3 normal;
in vec2 texCoord;

uniform lightInfo {
	vec4 position;
	vec3 color;
	vec3 amb;
	vec3 diff;
	vec3 spec;
	int spec_exp; //TODO: Have this here or in other location?
};

uniform sampler2D Tex1;

// We opt for a set material, because we're only texturing the ground.
void main()
{
	vec3 kA = vec3(1.0, 1.0, 1.0);
	vec3 kD = vec3(0.9, 0.9, 0.9);
	vec3 kS = vec3(0.1, 0.1, 0.1);

	vec3 n = normalize(normal); 
	vec3 s = normalize(vec3(position) - vert_position);
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-s, n);
	vec3 amb_comp = amb * kA;
	float sDotNorm = max(dot(s, n), 0.0);
	vec3 diff_comp = diff * kD * sDotNorm;
	vec3 spec_comp = vec3(0.0);
	if (sDotNorm > 0.0 )
	{
		spec_comp = spec * kS * pow(max(dot(r, v), 0.0), 10.0f);
	}
	vec4 texColor = texture(Tex1, texCoord);
	fragColor = texColor *  vec4((amb_comp + diff_comp), 1.0) + vec4(spec_comp, 1.0);
}