#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class PhongShading
{
private:
	struct Uniform
	{
		Uniform();

		GLint CamPos;
		GLint Projection;
		GLint View;
		GLint World;
		GLint MatDiffuse;
		GLint MatSpecular;
		GLint MatEmissive;
		GLint DirLightAmbient;
		GLint DirLightDiffuse;
		GLint DirLightSpecular;
		GLint DirLightDir;
		GLint FogStart;
		GLint FogEnd;
		GLint FogColor;
	};

	GLuint m_program;
	Uniform m_uniform;
	glm::mat4& m_projection;
	glm::mat4& m_view;
	glm::vec3& m_camPos;
public:
	PhongShading(const char* vs_filepath, const char* fs_filepath, glm::mat4& projection, glm::mat4& view, glm::vec3& camPos);

	void Process() const;
	void Use() const;
	GLuint GetProgram() const;
	void SetCamPos(const glm::vec3& camPos) const;
	void SetProjection(const glm::mat4& projection) const;
	void SetView(const glm::mat4& view) const;
	void SetWorld(const glm::mat4& world) const;
	void SetDirLightAmbient(const glm::vec3& ambient) const;
	void SetDirLightDiffuse(const glm::vec3& diffuse) const;
	void SetDirLightSpecular(const glm::vec3& specular) const;
	void SetDirLightDirection(const glm::vec3& direction) const;
	void SetFogStart(const float& start) const;
	void SetFogEnd(const float& end) const;
	void SetFogColor(const glm::vec3& color) const;

	~PhongShading();
};