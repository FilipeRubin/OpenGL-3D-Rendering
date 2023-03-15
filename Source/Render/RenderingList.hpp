#pragma once
#include <glad/glad.h>
//#include "RenderingItem.hpp"

class RenderingItem;

class RenderingList
{
private:
	GLuint          m_shaderProgram;
	GLint           m_camPosUniform;
	GLint           m_worldUniform;
	GLint           m_projectionUniform;
	GLint           m_viewUniform;
	RenderingItem** m_renderList;
	GLuint          m_count;
public:
	RenderingList(GLuint shaderProgram);
	void Add(RenderingItem& item);
	void Render() const;
	void SortByDistance(const glm::vec3& origin);
	void SetCamPos(const glm::vec3& camPos) const;
	void SetProjection(const glm::mat4& projection) const;
	void SetView(const glm::mat4& view) const;
	~RenderingList();
};