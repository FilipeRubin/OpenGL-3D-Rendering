#pragma once
#include "Shader.hpp"
#include <GLFW/glfw3.h>

class PostProcessing
{
private:
	GLuint m_framebuffer;
	GLuint m_texture;
	GLuint m_renderbuffer;
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_shaderProgram;
	GLFWwindow*& m_pWindow;
	int m_lastWindowX;
	int m_lastWindowY;
public:
	PostProcessing(GLFWwindow*& pWindow, const char* vs_filepath, const char* fs_filepath);
	void Process();
	void Render() const;
	~PostProcessing();
	PostProcessing& operator = (const PostProcessing&) = delete;
};