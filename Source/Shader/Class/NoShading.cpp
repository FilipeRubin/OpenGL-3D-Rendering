#include "NoShading.hpp"
#include "../Shader.hpp"

NoShading::Uniform::Uniform() :
	CamPos(0U),
	Projection(0U),
	View(0U),
	World(0U),
	MatDiffuse(0U),
	FogStart(0U),
	FogEnd(0U),
	FogColor(0U)
{}

NoShading::NoShading(const char* vs_filepath, const char* fs_filepath)
	:m_program(0U), m_uniform(Uniform())
{
	m_program = GenShaderProgram(vs_filepath, fs_filepath);

	m_uniform.CamPos = glGetUniformLocation(m_program, "u_cameraPos");
	m_uniform.Projection = glGetUniformLocation(m_program, "u_projection");
	m_uniform.View = glGetUniformLocation(m_program, "u_view");
	m_uniform.World = glGetUniformLocation(m_program, "u_world");
	m_uniform.MatDiffuse = glGetUniformLocation(m_program, "u_material.diffuse");
	m_uniform.FogStart = glGetUniformLocation(m_program, "u_fog.start");
	m_uniform.FogEnd = glGetUniformLocation(m_program, "u_fog.end");
	m_uniform.FogColor = glGetUniformLocation(m_program, "u_fog.color");

	glUseProgram(m_program);
	glUniform1i(m_uniform.MatDiffuse, 0);
}

void NoShading::Use() const
{
	glUseProgram(m_program);
}

GLuint NoShading::GetProgram() const
{
	return m_program;
}

void NoShading::SetCamPos(const glm::vec3& camPos) const
{
	glUniform3f(m_uniform.CamPos, camPos.x, camPos.y, camPos.z);
}

void NoShading::SetProjection(const glm::mat4& projection) const
{
	glUniformMatrix4fv(m_uniform.Projection, 1, GL_FALSE, &projection[0][0]);
}

void NoShading::SetView(const glm::mat4& view) const
{
	glUniformMatrix4fv(m_uniform.View, 1, GL_FALSE, &view[0][0]);
}

void NoShading::SetWorld(const glm::mat4& world) const
{
	glUniformMatrix4fv(m_uniform.World, 1, GL_FALSE, &world[0][0]);
}

void NoShading::SetFogStart(const float& start) const
{
	glUniform1f(m_uniform.FogStart, start);
}

void NoShading::SetFogEnd(const float& end) const
{
	glUniform1f(m_uniform.FogEnd, end);
}

void NoShading::SetFogColor(const glm::vec3& color) const
{
	glUniform3f(m_uniform.FogColor, color.r, color.g, color.b);
}

NoShading::~NoShading()
{
	glDeleteProgram(m_program);
}