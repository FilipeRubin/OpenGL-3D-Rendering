#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shininess;
};

struct Fog
{
	float start;
	float end;
	vec3 color;
};

in vec3 f_pos;
in vec2 f_uv;

out vec4 fragColor;

uniform vec3 u_cameraPos;

uniform Material u_material;
uniform Fog u_fog;

void main()
{
	// Pre-calculate expensive things
	vec4 fragDiffuse  = texture(u_material.diffuse, f_uv);
	vec3 viewDir      = normalize(u_cameraPos - f_pos);

	// FOG
	float distance = (length(u_cameraPos - f_pos) - u_fog.start) / (u_fog.end - u_fog.start);
	distance       = clamp(distance, 0.0, 1.0);
	vec4 finalFrag = vec4(mix(fragDiffuse.rgb, u_fog.color, distance), fragDiffuse.a);

	fragColor = finalFrag;
}