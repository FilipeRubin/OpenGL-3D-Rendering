#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Skybox
{
private:
	GLuint m_shaderProgram;
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_texture;
	GLint  m_uniformProj;
	GLint  m_uniformView;
	glm::mat4& m_projection;
	glm::mat4& m_view;
public:
	Skybox(const char* right_path, const char* left_path, const char* up_path, const char* down_path, const char* front_path, const char* back_path, glm::mat4& projection, glm::mat4& view);
	void Render() const;
	~Skybox();
};