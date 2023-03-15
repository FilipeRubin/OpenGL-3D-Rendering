#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

extern constexpr unsigned int NUM_POINT_LIGHTS = 1;

class PointLight
{
private:
	static PointLight s_pointLights[NUM_POINT_LIGHTS];
	static GLuint s_lampShaderProgram;
	static GLuint s_mainShaderProgram;
	static GLuint s_vbo;
	static GLuint s_vao;
	static GLuint s_ebo;
	static GLint  s_colorUniform;
	static GLint  s_projectionUniform;
	static GLint  s_viewUniform;
	static GLint  s_worldUniform;
	static GLint  s_camUniform;
	static GLuint s_lastID;
	static glm::mat4* s_pProjection;
	static glm::mat4* s_pView;
private:
	GLuint m_id;
	glm::mat4 m_world;
	glm::vec3 m_color;
public:
	static void Init(GLuint mainShaderProgram, glm::mat4* pProjection, glm::mat4* pView);
	static void Cleanup();
	static void Render();
	static PointLight& GetLight(int index);
	static void SetFog(float start, float end, const glm::vec3& color);
public:
	PointLight();
	void LightInfo(const glm::vec3& position, const glm::vec3& diffuse, const float& constant, const float& linear, const float& quadratic);
};