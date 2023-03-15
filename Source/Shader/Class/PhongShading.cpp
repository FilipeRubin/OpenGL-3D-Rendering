#include "PhongShading.hpp"
#include "../Shader.hpp"

PhongShading::Uniform::Uniform() :
	CamPos(0U),
	Projection(0U),
	View(0U),
	World(0U),
	MatDiffuse(0U),
	MatSpecular(0U),
	MatEmissive(0U),
	DirLightAmbient(0U),
	DirLightDiffuse(0U),
	DirLightSpecular(0U),
	DirLightDir(0U),
	FogStart(0U),
	FogEnd(0U),
	FogColor(0U)
{}

PhongShading::PhongShading(const char* vs_filepath, const char* fs_filepath, glm::mat4& projection, glm::mat4& view, glm::vec3& camPos)
	:m_program(0U), m_uniform(Uniform()), m_projection(projection), m_view(view), m_camPos(camPos)
{
	m_program = GenShaderProgram(vs_filepath, fs_filepath);

	m_uniform.CamPos = glGetUniformLocation(m_program, "u_cameraPos");
	m_uniform.Projection = glGetUniformLocation(m_program, "u_projection");
	m_uniform.View = glGetUniformLocation(m_program, "u_view");
	m_uniform.World = glGetUniformLocation(m_program, "u_world");
	m_uniform.MatDiffuse = glGetUniformLocation(m_program, "u_material.diffuse");
	m_uniform.MatSpecular = glGetUniformLocation(m_program, "u_material.specular");
	m_uniform.MatEmissive = glGetUniformLocation(m_program, "u_material.emissive");
	m_uniform.DirLightAmbient = glGetUniformLocation(m_program, "u_dirLight.ambient");
	m_uniform.DirLightDiffuse = glGetUniformLocation(m_program, "u_dirLight.diffuse");
	m_uniform.DirLightSpecular = glGetUniformLocation(m_program, "u_dirLight.specular");
	m_uniform.DirLightDir = glGetUniformLocation(m_program, "u_dirLight.direction");
	m_uniform.FogStart = glGetUniformLocation(m_program, "u_fog.start");
	m_uniform.FogEnd = glGetUniformLocation(m_program, "u_fog.end");
	m_uniform.FogColor = glGetUniformLocation(m_program, "u_fog.color");

	glUseProgram(m_program);
	glUniform1i(m_uniform.MatDiffuse, 0);
	glUniform1i(m_uniform.MatSpecular, 1);
	glUniform1i(m_uniform.MatEmissive, 2);
}

void PhongShading::Process() const
{
	glUseProgram(m_program);
	glUniformMatrix4fv(m_uniform.Projection, 1, GL_FALSE, &m_projection[0][0]);
	glUniformMatrix4fv(m_uniform.View, 1, GL_FALSE, &m_view[0][0]);
	glUniform3f(m_uniform.CamPos, -m_camPos.x, -m_camPos.y, -m_camPos.z);
}

void PhongShading::Use() const
{
	glUseProgram(m_program);
}

GLuint PhongShading::GetProgram() const
{
	return m_program;
}

void PhongShading::SetCamPos(const glm::vec3& camPos) const
{
	glUniform3f(m_uniform.CamPos, camPos.x, camPos.y, camPos.z);
}

void PhongShading::SetProjection(const glm::mat4& projection) const
{
	glUniformMatrix4fv(m_uniform.Projection, 1, GL_FALSE, &projection[0][0]);
}

void PhongShading::SetView(const glm::mat4& view) const
{
	glUniformMatrix4fv(m_uniform.View, 1, GL_FALSE, &view[0][0]);
}

void PhongShading::SetWorld(const glm::mat4& world) const
{
	glUniformMatrix4fv(m_uniform.World, 1, GL_FALSE, &world[0][0]);
}

void PhongShading::SetDirLightAmbient(const glm::vec3& ambient) const
{
	glUniform3f(m_uniform.DirLightAmbient, ambient.x, ambient.y, ambient.z);
}

void PhongShading::SetDirLightDiffuse(const glm::vec3& diffuse) const
{
	glUniform3f(m_uniform.DirLightDiffuse, diffuse.x, diffuse.y, diffuse.z);
}

void PhongShading::SetDirLightSpecular(const glm::vec3& specular) const
{
	glUniform3f(m_uniform.DirLightSpecular, specular.x, specular.y, specular.z);
}

void PhongShading::SetDirLightDirection(const glm::vec3& direction) const
{
	glUniform3f(m_uniform.DirLightDir, direction.x, direction.y, direction.z);
}

void PhongShading::SetFogStart(const float& start) const
{
	glUniform1f(m_uniform.FogStart, start);
}

void PhongShading::SetFogEnd(const float& end) const
{
	glUniform1f(m_uniform.FogEnd, end);
}

void PhongShading::SetFogColor(const glm::vec3& color) const
{
	glUniform3f(m_uniform.FogColor, color.r, color.g, color.b);
}

PhongShading::~PhongShading()
{
	glDeleteProgram(m_program);
}