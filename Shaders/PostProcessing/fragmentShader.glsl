#version 330 core

in vec2 v_out_tex;

out vec4 f_fragColor;

uniform sampler2D u_texture;
const float offset = 1.0 / 300.0;

void main()
{
	vec2 offsets[9] = vec2[](
		vec2(-offset,  offset), vec2(0.0f,  offset), vec2(offset,  offset),
		vec2(-offset,    0.0f), vec2(0.0f,    0.0f), vec2(offset,    0.0f),
		vec2(-offset, -offset), vec2(0.0f, -offset), vec2(offset, -offset)
	);

	float kernel[9] = float[](
		1.0f,  1.0f, 1.0f,
		1.0f, -8.0f, 1.0f,
		1.0f,  1.0f, 1.0f
	);

	vec3 sampleTex[9];

	for (int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(u_texture, v_out_tex.st + offsets[i]));
	}
	
	vec3 col = vec3(0.0);
	
	for (int i = 0; i < 9; i++)
	{
		col += sampleTex[i] * kernel[i];
	}

	vec4 originalCol = texture(u_texture, v_out_tex);

	f_fragColor = vec4(col, 1.0) + originalCol;
}