#version 330 core

layout(location = 0) in vec3 v_pos;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_world;

out vec3 f_pos;

void main()
{
	gl_Position = u_projection * u_view * u_world * vec4(v_pos, 1.0);
	f_pos = vec3(u_world * vec4(v_pos, 1.0));
}