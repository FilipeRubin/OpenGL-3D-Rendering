#version 330 core

layout(location = 0) in vec3 v_in_pos;

out vec3 v_out_tex;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	v_out_tex = v_in_pos;
	gl_Position = (u_projection * u_view * vec4(v_in_pos, 1.0)).xyww;
}