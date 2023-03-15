#pragma once
#include <GLFW/glfw3.h>

class PlayerBase
{
protected:
	GLFWwindow* m_pWindow;
public:
	PlayerBase(GLFWwindow* pWindow);
	virtual void Process() = 0;
};