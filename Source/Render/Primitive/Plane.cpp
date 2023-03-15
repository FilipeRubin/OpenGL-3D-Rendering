#include "Plane.hpp"

static struct TexVertex
{
	float  x, y, z;
	float nx, ny, nz;
	float  u, v;
};

Plane::Plane(float width, float depth, bool fixedUV)
{
	width /= 2.0f;
	depth /= 2.0f;

	TexVertex vertices[]
	{
		{  width, 0.0f,  depth, 0.0f, 1.0f, 0.0f, fixedUV ? ( width + 0.5f) : 1.0f, fixedUV ? (-depth + 0.5f) : 0.0f},
		{  width, 0.0f, -depth, 0.0f, 1.0f, 0.0f, fixedUV ? ( width + 0.5f) : 1.0f, fixedUV ? ( depth + 0.5f) : 1.0f},
		{ -width, 0.0f, -depth, 0.0f, 1.0f, 0.0f, fixedUV ? (-width + 0.5f) : 0.0f, fixedUV ? ( depth + 0.5f) : 1.0f},
		{ -width, 0.0f,  depth, 0.0f, 1.0f, 0.0f, fixedUV ? (-width + 0.5f) : 0.0f, fixedUV ? (-depth + 0.5f) : 0.0f}
	};

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)0);
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)12);
	glVertexAttribPointer(2U, 2, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)24);
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glEnableVertexAttribArray(2U);
}

void Plane::Render() const
{
	RenderingItem::Render();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}