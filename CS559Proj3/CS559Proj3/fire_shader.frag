#version 400
#extension GL_ARB_separate_shader_objects : enable
//Used for the skybox.

layout (location = 0) out vec4 fragColor;

in vec3 vert_position;
in vec3 normal;
in vec2 texCoord;

uniform float time;
uniform sampler3D noiseTex;

// We opt for a set material, because we're only texturing the ground.
void main()
{
	vec4 texColor = texture(noiseTex, vec3(texCoord, time/15000.0));

	float intensity;
	intensity += abs(texColor[0] - 0.25);
	intensity += abs(texColor[1] - 0.125);
	intensity += abs(texColor[2] - 0.0625);
	intensity += abs(texColor[3] - 0.03125); //Add varying amounts based on octave

	intensity = clamp (intensity, 0.0, 1.0); //Intensify effect

	vec3 color = mix(vec3(0.8, 0.7, 0.0), vec3(0.6, 0.1, 0.0), intensity);
	
	fragColor = vec4(color, 1.0);

	//fragColor = mix(interComp, compThree, 0.5);
	//fragColor = mix(vec4(1.0, 0.0, 0.0, 1.0), vec4(texColor_a.r, texColor_b.g, texColor_c.b, 1.0), 0.5);
}