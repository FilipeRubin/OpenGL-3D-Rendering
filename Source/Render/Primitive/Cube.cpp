#include "Cube.hpp"

static struct TexVertex
{
	float  x, y, z;
	float nx, ny, nz;
	float  u, v;
};

Cube::Cube(float width, float height, float depth)
	:RenderingItem()
{
	width /= 2.0f;
	height /= 2.0f;
	depth /= 2.0f;

	TexVertex vertices[]
	{
		// Back face
		{  width, -height, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
		{  width,  height, depth, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
		{ -width,  height, depth, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{ -width, -height, depth, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		// Right face
		{ width, -height, -depth, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
		{ width,  height, -depth, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{ width,  height,  depth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
		{ width, -height,  depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		// Front face
		{ -width, -height, -depth, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
		{ -width,  height, -depth, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
		{  width,  height, -depth, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
		{  width, -height, -depth, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
		// Left face
		{ -width, -height,  depth, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
		{ -width,  height,  depth, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{ -width,  height, -depth, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
		{ -width, -height, -depth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		// Top face
		{  width, height,  depth, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
		{  width, height, -depth, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
		{ -width, height, -depth, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{ -width, height,  depth, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
		// Bottom face
		{  width, -height, -depth, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
		{  width, -height,  depth, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
		{ -width, -height,  depth, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f},
		{ -width, -height, -depth, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f}
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

void Cube::Render() const
{
	RenderingItem::Render();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
}