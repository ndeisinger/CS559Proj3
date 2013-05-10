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
	vec4 texColor = texture(noiseTex, vec3(texCoord, time/150.0));
	vec4 compOne = texColor.r * vec4(1.0, 0.2, 0.0, 1.0);
	vec4 compTwo = texColor.g * vec4(1.0, 0.5, 0.0, 1.0);
	vec4 compThree = texColor.b * vec4(1.0, 0.9, 0.0, 1.0);
	vec4 interComp = mix(compOne, compTwo, 0.5);

	fragColor = mix(interComp, compThree, 0.5);
	//fragColor = texColor;
}