#version 330 core

in vec3 v_out_tex;

out vec4 f_color;

uniform samplerCube u_skybox;

void main()
{
	f_color = texture(u_skybox, v_out_tex);
}