#version 330 core

struct Fog
{
	float start;
	float end;
	vec3 color;
};

uniform vec3 u_cameraPos;
uniform vec3 u_color;
uniform Fog u_fog;

in vec3 f_pos;

out vec4 fragColor;

void main()
{
	float distance = (length(u_cameraPos - f_pos) - u_fog.start) / (u_fog.end - u_fog.start);
	distance       = clamp(distance, 0.0, 1.0);
	vec3 finalFrag = mix(u_color, u_fog.color, distance);

	fragColor = vec4(finalFrag, 1.0);
}