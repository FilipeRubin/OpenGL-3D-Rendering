#include <glm/gtx/norm.hpp>
#include "RenderingList.hpp"
#include "RenderingItem.hpp"

inline static void Swap(void*& a, void*& b)
{
	void* temp = a;
	a = b;
	b = temp;
}

RenderingList::RenderingList(GLuint shaderProgram)
	:m_shaderProgram(shaderProgram), m_camPosUniform(0), m_worldUniform(0), m_projectionUniform(0), m_viewUniform(0), m_renderList(nullptr), m_count(0U)
{
	m_camPosUniform = glGetUniformLocation(shaderProgram, "u_cameraPos");
	m_worldUniform = glGetUniformLocation(shaderProgram, "u_world");
	m_projectionUniform = glGetUniformLocation(shaderProgram, "u_projection");
	m_viewUniform = glGetUniformLocation(shaderProgram, "u_view");
}

void RenderingList::Add(RenderingItem& item)
{
	if (m_count == 0U)
	{
		m_renderList = new RenderingItem*[1];
		m_renderList[0] = &item;
	}
	else
	{
		RenderingItem** newList = new RenderingItem*[m_count + 1];
		for (GLuint i = 0; i < m_count; i++)
		{
			newList[i] = m_renderList[i];
		}
		newList[m_count] = &item;
		delete[m_count] m_renderList;
		m_renderList = newList;
	}

	m_count++;
}

void RenderingList::Render() const
{
	glUseProgram(m_shaderProgram);
	for (GLuint i = 0; i < m_count; i++)
	{
		glm::mat4 world = m_renderList[i]->m_translationMat * m_renderList[i]->m_rotationXMat * m_renderList[i]->m_rotationYMat * m_renderList[i]->m_rotationZMat * m_renderList[i]->m_scaleMat;
		glUniformMatrix4fv(m_worldUniform, 1, GL_FALSE, &world[0][0]);
		m_renderList[i]->Render();
	}
}

void RenderingList::SortByDistance(const glm::vec3& origin)
{
	RenderingItem** tempList = new RenderingItem*[m_count];
	memset(tempList, 0, sizeof(RenderingItem*) * m_count);
	bool* sorted = new bool[m_count];
	memset(sorted, 0, m_count);
	
	// Basic sorting algorithm. Must be replaced with something better in the future
	for (int i = 0; i < m_count; i++)
	{
		RenderingItem* highestPtr = nullptr;
		float          highestDist = 0.0f;
		int            highestIndex = -1;

		for (int j = 0; j < m_count; j++)
		{
			if (sorted[j])
				continue;
			float currDist = glm::length2(m_renderList[j]->m_translation - origin);
			if (currDist >= highestDist)
			{
				highestDist = currDist;
				highestPtr = m_renderList[j];
				highestIndex = j;
			}
		}
		tempList[i] = highestPtr;
		sorted[highestIndex] = true;
	}

	memcpy(m_renderList, tempList, sizeof(RenderingItem*) * m_count);

	delete[m_count] tempList;
	delete[m_count] sorted;
}

void RenderingList::SetCamPos(const glm::vec3& camPos) const
{
	glUniform3f(m_camPosUniform, camPos.x, camPos.y, camPos.z);
}

void RenderingList::SetProjection(const glm::mat4& projection) const
{
	glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, &projection[0][0]);
}

void RenderingList::SetView(const glm::mat4& view) const
{
	glUniformMatrix4fv(m_viewUniform, 1, GL_FALSE, &view[0][0]);
}

RenderingList::~RenderingList()
{
	delete[m_count] m_renderList;
}