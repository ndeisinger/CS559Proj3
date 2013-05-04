#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 3) in vec2 vertex_tex_coord;

out vec3 vert_position;
out vec3 normal;
out vec2 texCoord;
out vec4 shadowCoord;

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;
uniform mat4 shadow_matrix;

void main()
{
	texCoord = vertex_tex_coord;
	normal = normalize(n_matrix * vertex_normal);
	vert_position = vec3(mv_matrix * vec4(vertex_position, 1.0));
	shadowCoord = (shadow_matrix * vertex_position);
	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
}