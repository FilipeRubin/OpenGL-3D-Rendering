#version 330 core

layout(location = 0) in vec3 v_pos;
//layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_uv;

out vec3 f_pos;
out vec2 f_uv;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_world;

void main()
{
	gl_Position = u_projection * u_view * u_world * vec4(v_pos, 1.0);
	f_pos       = v_pos;
	f_uv        = v_uv;
}