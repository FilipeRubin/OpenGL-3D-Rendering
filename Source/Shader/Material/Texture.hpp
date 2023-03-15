#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
//#include "../../Render/RenderingList.hpp"

class RenderingList;

class Texture
{
private:
	GLuint* m_texture;
	GLuint* m_fbo;
	GLuint* m_rbo;
	glm::mat4* m_projection;
	glm::mat4* m_view;
	glm::vec3* m_camPos;
	int* m_width;
	int* m_height;
	int* m_pInstanceCount;
public:
	Texture();
	Texture(const char* path);
	Texture(const glm::mat4& view, int width = 128, int height = 128);
	Texture(const Texture& other);
	void SetProjection(float fov, float aspectRatio, float near = 0.1f, float far = 25.0f);
	void SetView(const glm::vec3& eye, const glm::vec3& at);
	void Process(const RenderingList** renderingLists, int size);
	void Use() const;
	Texture& operator = (const Texture& other);
	~Texture();
};