#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;

out vec3 position;
out vec3 Color;

void main()
{
	Color = vertex_position;
	//gl_Position = vec4(vertex_color, 1.0); 
	position = vertex_position;
//	position = vec3(mv_matrix * vec4(vertex_position, 1.0));
	//gl_Position = vec4(position, 1.0);
	gl_Position =  mvp_matrix * vec4(position, 1.0);
}