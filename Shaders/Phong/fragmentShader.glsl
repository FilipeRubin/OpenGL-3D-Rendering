#version 330 core

#define NUM_POINT_LIGHTS 1

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 color;

	float constant;
	float linear;
	float quadratic;
};

struct Fog
{
	float start;
	float end;
	vec3 color;
};

in vec3 f_pos;
in vec3 f_normal;
in vec2 f_uv;

out vec4 fragColor;

uniform vec3 u_cameraPos;

uniform Material u_material;
uniform DirectionalLight u_dirLight;
uniform PointLight u_pointLight[NUM_POINT_LIGHTS];
uniform Fog u_fog;

vec4 CalculateDirectionalLight(vec4 fragDiffuse, vec3 fragSpecular, vec3 fragDir, vec3 viewDir)
{
	// Ambient
	vec4 ambient = fragDiffuse * vec4(u_dirLight.ambient, 1.0);

	// Diffuse
	vec3 lightDir = normalize(u_dirLight.direction);
	float intensity = dot(-lightDir, fragDir);
	vec4 diffuse = vec4(fragDiffuse.rgb * u_dirLight.diffuse * intensity, fragDiffuse.a);

	// Specular
	vec3 reflectDir = reflect(lightDir, fragDir);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
	vec4 specular = vec4(u_dirLight.specular * fragSpecular * specularAmount, specularAmount);

	return max(ambient, diffuse) + specular;
}

vec4 CalculatePointLight(PointLight pointLight, vec4 fragDiffuse, vec3 fragSpecular, vec3 fragDir, vec3 viewDir)
{
	vec3 lightDir = normalize(pointLight.position - f_pos);

	// Diffuse
	vec4 diffuse = vec4(max(dot(lightDir, fragDir), 0.0) * fragDiffuse.rgb * pointLight.color, 0.0);

	// Specular
	vec3 reflectDir = reflect(-lightDir, fragDir);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
	vec4 specular = vec4(fragSpecular * pointLight.color * specularAmount, specularAmount);

	// Attenuation
	float distance = length(pointLight.position - f_pos);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
	
	diffuse = vec4(diffuse.rgb * attenuation, diffuse.a);
	specular = vec4(specular.rgb * attenuation, specular.a);
	
	return diffuse + specular;
}

void main()
{
	// Pre-calculate expensive things
	vec4 fragDiffuse  = texture(u_material.diffuse, f_uv);
	vec3 fragSpecular = vec3(texture(u_material.specular, f_uv));
	vec3 fragDir      = normalize(f_normal);
	vec3 viewDir      = normalize(u_cameraPos - f_pos);

	// Directional light
	vec4 shadedFrag = CalculateDirectionalLight(fragDiffuse, fragSpecular, fragDir, viewDir);

	// Point lights
	for (int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		shadedFrag += CalculatePointLight(u_pointLight[i], fragDiffuse, fragSpecular, fragDir, viewDir);
	}

	// Emissive
	shadedFrag += vec4(texture(u_material.emissive, f_uv).rgb, 0.0);

	// FOG
	float distance = (length(u_cameraPos - f_pos) - u_fog.start) / (u_fog.end - u_fog.start);
	distance       = clamp(distance, 0.0, 1.0);
	vec4 finalFrag = vec4(mix(shadedFrag.rgb, u_fog.color, distance), shadedFrag.a);

	fragColor = finalFrag;
}