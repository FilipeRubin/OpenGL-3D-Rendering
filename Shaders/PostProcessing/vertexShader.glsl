#version 330 core

layout(location = 0) in vec2 v_in_pos;
layout(location = 1) in vec2 v_in_tex;

out vec2 v_out_tex;

void main()
{
	gl_Position = vec4(v_in_pos, 0.0, 1.0);
	v_out_tex = v_in_tex;
}