#include "Pyramid.hpp"

static struct TexVertex
{
	float  x, y, z;
	float nx, ny, nz;
	float  u, v;
};

Pyramid::Pyramid(float width, float height)
{
	width /= 2.0f;

	TexVertex vertices[]
	{
		// Front face
		{  width,   0.0f,  width, 0.0f, 0.4472f, 0.8944, 1.0f, 0.0f },
		{   0.0f, height,   0.0f, 0.0f, 0.4472f, 0.8944, 0.5f, 1.0f },
		{ -width,   0.0f,  width, 0.0f, 0.4472f, 0.8944, 0.0f, 0.0f },
		// Right face
		{  width,   0.0f, -width, 0.8944f, 0.4472f, 0.0f, 1.0f, 0.0f },
		{   0.0f, height,   0.0f, 0.8944f, 0.4472f, 0.0f, 0.5f, 1.0f },
		{  width,   0.0f,  width, 0.8944f, 0.4472f, 0.0f, 0.0f, 0.0f },
		// Back face
		{ -width,   0.0f, -width, 0.0f, 0.4472f, -0.8944f, 1.0f, 0.0f },
		{   0.0f, height,   0.0f, 0.0f, 0.4472f, -0.8944f, 0.5f, 1.0f },
		{  width,   0.0f, -width, 0.0f, 0.4472f, -0.8944f, 0.0f, 0.0f },
		// Left face
		{ -width,   0.0f,  width, -0.8944f, 0.4472f, 0.0f, 1.0f, 0.0f },
		{   0.0f, height,   0.0f, -0.8944f, 0.4472f, 0.0f, 0.5f, 1.0f },
		{ -width,   0.0f, -width, -0.8944f, 0.4472f, 0.0f, 0.0f, 0.0f },
		// Bottom face
		{  width, 0.0f, -width, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f },
		{  width, 0.0f,  width, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f },
		{ -width, 0.0f,  width, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f },
		{ -width, 0.0f, -width, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f },
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

void Pyramid::Render() const
{
	RenderingItem::Render();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
}