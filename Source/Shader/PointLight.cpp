#include "PointLight.hpp"
#include "Shader.hpp"
#include <string>
#include <glm/gtc/type_ptr.hpp>

PointLight PointLight::s_pointLights[NUM_POINT_LIGHTS];
GLuint PointLight::s_lampShaderProgram = 0U;
GLuint PointLight::s_mainShaderProgram = 0U;
GLuint PointLight::s_vbo = 0U;
GLuint PointLight::s_vao = 0U;
GLuint PointLight::s_ebo = 0U;
GLint PointLight::s_colorUniform = 0;
GLint PointLight::s_projectionUniform = 0;
GLint PointLight::s_viewUniform = 0;
GLint PointLight::s_worldUniform = 0;
GLint PointLight::s_camUniform = 0;
GLuint PointLight::s_lastID = 0U;
glm::mat4* PointLight::s_pProjection = nullptr;
glm::mat4* PointLight::s_pView = nullptr;

void PointLight::Init(GLuint mainShaderProgram, glm::mat4* pProjection, glm::mat4* pView)
{
	s_mainShaderProgram = mainShaderProgram;
	s_lampShaderProgram = GenShaderProgram("Shaders\\Lamp\\vertexShader.glsl", "Shaders\\Lamp\\fragmentShader.glsl");

	s_colorUniform      = glGetUniformLocation(s_lampShaderProgram, "u_color");
	s_projectionUniform = glGetUniformLocation(s_lampShaderProgram, "u_projection");
	s_viewUniform       = glGetUniformLocation(s_lampShaderProgram, "u_view");
	s_worldUniform      = glGetUniformLocation(s_lampShaderProgram, "u_world");
	s_camUniform        = glGetUniformLocation(s_lampShaderProgram, "u_cameraPos");

	s_pProjection = pProjection;
	s_pView = pView;

	GLfloat vertices[]
	{
		 0.2f,  0.0f,  0.0f, // 0 Right
		 0.0f,  0.0f,  0.2f, // 1 Back
		-0.2f,  0.0f,  0.0f, // 2 Left
		 0.0f,  0.0f, -0.2f, // 3 Front
		 0.0f,  0.2f,  0.0f, // 4 Top
		 0.0f, -0.2f,  0.0f  // 5 Bottom
	};

	GLubyte indices[]
	{
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		3, 4, 0,
		5, 3, 0,
		5, 0, 1,
		5, 1, 2,
		5, 2, 3
	};

	glGenBuffers(1, &s_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &s_vao);
	glBindVertexArray(s_vao);
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(0U);

	glGenBuffers(1, &s_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void PointLight::Cleanup()
{
	glDeleteProgram(s_lampShaderProgram);
	glDeleteBuffers(1, &s_vbo);
	glDeleteVertexArrays(1, &s_vao);
	glDeleteBuffers(1, &s_ebo);
}

void PointLight::Render()
{
	glUseProgram(s_lampShaderProgram);
	glUniformMatrix4fv(s_projectionUniform, 1, GL_FALSE, &(*s_pProjection)[0][0]);
	glUniformMatrix4fv(s_viewUniform, 1, GL_FALSE, &(*s_pView)[0][0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
	glBindVertexArray(s_vao);

	for (int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		glUniform3f(s_colorUniform, s_pointLights[i].m_color.x, s_pointLights[i].m_color.y, s_pointLights[i].m_color.z);
		glUniformMatrix4fv(s_worldUniform, 1, GL_FALSE, glm::value_ptr(s_pointLights[i].m_world));
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, (void*)0);
	}
}

PointLight& PointLight::GetLight(int index)
{
	return s_pointLights[index];
}

void PointLight::SetFog(float start, float end, const glm::vec3& color)
{
	GLint uFogStart = glGetUniformLocation(s_lampShaderProgram, "u_fog.start");
	GLint uFogEnd   = glGetUniformLocation(s_lampShaderProgram, "u_fog.end");
	GLint uFogColor = glGetUniformLocation(s_lampShaderProgram, "u_fog.color");

	glUseProgram(s_lampShaderProgram);
	glUniform1f(uFogStart, start);
	glUniform1f(uFogEnd, end);
	glUniform3f(uFogColor, color.x, color.y, color.z);
}

PointLight::PointLight()
	:m_id(s_lastID), m_world(glm::mat4(1.0f)), m_color(glm::vec3())
{
	s_lastID++;
}

void PointLight::LightInfo(const glm::vec3& position, const glm::vec3& color, const float& constant, const float& linear, const float& quadratic)
{
	std::string uniformStr = "u_pointLight[" + std::to_string(m_id) + "].";
	std::string posStr     = uniformStr + "position";
	std::string colorStr   = uniformStr + "color";
	std::string constStr   = uniformStr + "constant";
	std::string linearStr  = uniformStr + "linear";
	std::string quadStr    = uniformStr + "quadratic";

	glUseProgram(s_mainShaderProgram);

	// Position
	GLint uniLoc = glGetUniformLocation(s_mainShaderProgram, posStr.c_str());
	glUniform3f(uniLoc, position.x, position.y, position.z);
	m_world = glm::translate(glm::mat4(1.0f), position);

	// Diffuse
	uniLoc = glGetUniformLocation(s_mainShaderProgram, colorStr.c_str());
	glUniform3f(uniLoc, color.x, color.y, color.z);
	m_color = color;

	// Constant
	uniLoc = glGetUniformLocation(s_mainShaderProgram, constStr.c_str());
	glUniform1f(uniLoc, constant);

	// Linear
	uniLoc = glGetUniformLocation(s_mainShaderProgram, linearStr.c_str());
	glUniform1f(uniLoc, linear);
	
	// Quadratic
	uniLoc = glGetUniformLocation(s_mainShaderProgram, quadStr.c_str());
	glUniform1f(uniLoc, quadratic);
}
