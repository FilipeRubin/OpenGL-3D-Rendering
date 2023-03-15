#include "PostProcessing.hpp"

PostProcessing::PostProcessing(GLFWwindow*& pWindow, const char* vs_filepath, const char* fs_filepath)
	:m_framebuffer(0U), m_texture(0U), m_renderbuffer(0U), m_vbo(0U), m_vao(0U), m_shaderProgram(0U), m_pWindow(pWindow), m_lastWindowX(0), m_lastWindowY(0)
{
	glfwGetWindowSize(pWindow, &m_lastWindowX, &m_lastWindowY);

	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_lastWindowX, m_lastWindowY, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	glGenRenderbuffers(1, &m_renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_lastWindowX, m_lastWindowY);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLfloat quad[]
	{
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f
	};

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, 16, (void*)0);
	glVertexAttribPointer(1U, 2, GL_FLOAT, GL_FALSE, 16, (void*)8);
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);

	m_shaderProgram = GenShaderProgram(vs_filepath, fs_filepath);
}

void PostProcessing::Process()
{
	int newX, newY;
	glfwGetWindowSize(m_pWindow, &newX, &newY);
	glViewport(0, 0, newX, newY);

	if (newX != m_lastWindowX or newY != m_lastWindowY)
	{
		m_lastWindowX = newX;
		m_lastWindowY = newY;
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_lastWindowX, m_lastWindowY, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_lastWindowX, m_lastWindowY);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessing::Render() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

PostProcessing::~PostProcessing()
{
	glDeleteFramebuffers(1, &m_framebuffer);
	glDeleteTextures(1, &m_texture);
	glDeleteRenderbuffers(1, &m_renderbuffer);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteProgram(m_shaderProgram);
}