#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class NoShading
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
		GLint FogStart;
		GLint FogEnd;
		GLint FogColor;
	};

	GLuint m_program;
	Uniform m_uniform;
public:
	NoShading(const char* vs_filepath, const char* fs_filepath);
	void Use() const;
	GLuint GetProgram() const;
	void SetCamPos(const glm::vec3& camPos) const;
	void SetProjection(const glm::mat4& projection) const;
	void SetView(const glm::mat4& view) const;
	void SetWorld(const glm::mat4& world) const;
	void SetFogStart(const float& start) const;
	void SetFogEnd(const float& end) const;
	void SetFogColor(const glm::vec3& color) const;
	~NoShading();
};