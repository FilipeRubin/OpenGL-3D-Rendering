#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"
#include "../../Render/RenderingList.hpp"

extern int windowSizeX;
extern int windowSizeY;

Texture::Texture()
	:m_texture(new GLuint(0U)), m_fbo(new GLuint(0U)), m_rbo(new GLuint(0U)), m_projection(new glm::mat4(1.0f)), m_view(new glm::mat4(1.0f)), m_camPos(new glm::vec3()), m_width(new int(128)), m_height(new int(128)), m_pInstanceCount(new int(1))
{
}

Texture::Texture(const char* path)
	:m_texture(new GLuint(0U)), m_fbo(new GLuint(0U)), m_rbo(new GLuint(0U)), m_projection(new glm::mat4(1.0f)), m_view(new glm::mat4(1.0f)), m_camPos(new glm::vec3()), m_width(new int(0)), m_height(new int(0)), m_pInstanceCount(new int(1))
{
	glGenTextures(1, m_texture);
	glBindTexture(GL_TEXTURE_2D, *m_texture);
	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);
	GLubyte* texData = stbi_load(path, &width, &height, &numChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, numChannels == 3 ? GL_RGB : GL_RGBA, width, height, 0, numChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(texData);
}

Texture::Texture(const glm::mat4& view, int width, int height)
	:m_texture(new GLuint(0U)), m_fbo(new GLuint(0U)), m_rbo(new GLuint(0U)), m_projection(new glm::mat4(1.0f)), m_view(new glm::mat4(view)), m_camPos(new glm::vec3()), m_width(new int(width)), m_height(new int(height)), m_pInstanceCount(new int(1))
{
	glGenFramebuffers(1, m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, *m_fbo);

	glGenTextures(1, m_texture);
	glBindTexture(GL_TEXTURE_2D, *m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glGenRenderbuffers(1, m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, *m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *m_texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *m_rbo);
}

Texture::Texture(const Texture& other)
	:m_texture(other.m_texture), m_fbo(other.m_fbo), m_rbo(other.m_rbo), m_projection(other.m_projection), m_view(other.m_view), m_camPos(other.m_camPos), m_width(other.m_width), m_height(other.m_height), m_pInstanceCount(other.m_pInstanceCount)
{
	(*m_pInstanceCount)++;
}

void Texture::SetProjection(float fov, float aspectRatio, float near, float far)
{
	*m_projection = glm::perspective(fov, aspectRatio, near, far);
}

void Texture::SetView(const glm::vec3& eye, const glm::vec3& at)
{
	*m_camPos = eye;
	*m_view = glm::lookAt(eye, at, glm::vec3(0.0f, -1.0f, 0.0f));
}

void Texture::Process(const RenderingList** renderingLists, int size)
{
	if (!m_fbo)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, *m_fbo);
	glViewport(0, 0, *m_width, *m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < size; i++)
	{
		renderingLists[i]->SetCamPos(*m_camPos);
		renderingLists[i]->SetProjection(*m_projection);
		renderingLists[i]->SetView(*m_view);
		renderingLists[i]->Render();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, windowSizeX, windowSizeY);
}

void Texture::Use() const
{
	if ((*m_texture) != 0)
		glBindTexture(GL_TEXTURE_2D, *m_texture);
	else
		glBindTexture(GL_TEXTURE_2D, 0);
}

Texture& Texture::operator = (const Texture& other)
{
	if (this != &other)
	{
		(*m_pInstanceCount)--;

		if (*m_pInstanceCount == 0)
		{
			if (*m_texture)
				glDeleteTextures(1, m_texture);
			if (*m_fbo)
				glDeleteFramebuffers(1, m_fbo);
			if (*m_rbo)
				glDeleteRenderbuffers(1, m_rbo);

			delete m_texture;
			delete m_fbo;
			delete m_rbo;
			delete m_projection;
			delete m_view;
			delete m_width;
			delete m_height;
			delete m_pInstanceCount;
		}

		m_texture        = other.m_texture;
		m_fbo            = other.m_fbo;
		m_rbo            = other.m_rbo;
		m_projection     = other.m_projection;
		m_view           = other.m_view;
		m_camPos         = other.m_camPos;
		m_width          = other.m_width;
		m_height         = other.m_height;
		m_pInstanceCount = other.m_pInstanceCount;
		(*m_pInstanceCount)++;
	}

	return *this;
}

Texture::~Texture()
{
	if (m_pInstanceCount)
	{
		(*m_pInstanceCount)--;

		if (*m_pInstanceCount == 0)
		{
			if (*m_texture)
				glDeleteTextures(1, m_texture);
			if (*m_fbo)
				glDeleteFramebuffers(1, m_fbo);
			if (*m_rbo)
				glDeleteRenderbuffers(1, m_rbo);

			delete m_texture;
			delete m_fbo;
			delete m_rbo;
			delete m_projection;
			delete m_view;
			delete m_width;
			delete m_height;
			delete m_pInstanceCount;
		}
	}
}