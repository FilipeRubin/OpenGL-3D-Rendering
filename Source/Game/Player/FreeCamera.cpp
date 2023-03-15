#include <glm/gtc/matrix_transform.hpp>
#include "FreeCamera.hpp"

#define PI 3.141592654f
#define CLAMP(value, min, max) value < min ? min : value > max ? max : value

extern float deltaTime;

FreeCamera::FreeCamera(GLFWwindow* pWindow, glm::mat4& view, glm::vec3& camPos)
	:PlayerBase(pWindow), m_view(view), m_camPos(camPos), m_camRot(glm::vec3(0.0f, glm::radians(-45.0f), 0.0f)), m_lastX(0.0), m_lastY(0.0)
{}

void FreeCamera::Process()
{
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

	double posx = 0.0, posy = 0.0;

	glfwGetCursorPos(m_pWindow, &posx, &posy);

	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		m_camRot.y += (float)(posx - m_lastX) * 0.01f;
		m_camRot.x += (float)(posy - m_lastY) * 0.01f;

		m_camRot.x = CLAMP(m_camRot.x, -PI / 2.0f, PI / 2.0f);
	}
	else
	{
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	m_lastX = posx;
	m_lastY = posy;

	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		direction.x -= sinf(m_camRot.y) * cosf(m_camRot.x);
		direction.z += cosf(m_camRot.y) * cosf(m_camRot.x);
		direction.y += sinf(m_camRot.x);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		direction.x += sinf(m_camRot.y) * cosf(m_camRot.x);
		direction.z -= cosf(m_camRot.y) * cosf(m_camRot.x);
		direction.y -= sinf(m_camRot.x);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		direction.x += cosf(m_camRot.y);
		direction.z += sinf(m_camRot.y);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		direction.x -= cosf(m_camRot.y);
		direction.z -= sinf(m_camRot.y);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_E) == GLFW_PRESS)
	{
		direction.z += cosf(m_camRot.y) * sinf(m_camRot.x);
		direction.x -= sinf(m_camRot.y) * sinf(m_camRot.x);
		direction.y -= cosf(m_camRot.x);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_Q) == GLFW_PRESS)
	{
		direction.z -= cosf(m_camRot.y) * sinf(m_camRot.x);
		direction.x += sinf(m_camRot.y) * sinf(m_camRot.x);
		direction.y += cosf(m_camRot.x);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		direction.y -= 1.0f;
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		direction.y += 1.0f;
	}
	// Lembrar de normalizar o movimento apenas no X e Z pra ver se fica melhor
	if (!(direction.x == 0.0f and direction.y == 0.0f and direction.z == 0.0f))
	{
		direction = glm::normalize(direction);
		direction *= deltaTime * (glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 5.0f : (glfwGetKey(m_pWindow, GLFW_KEY_LEFT_ALT) ? 0.25f : 2.5f));
	}

	m_camPos += direction;

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), m_camPos);
	glm::mat4 rotXMat = glm::rotate(glm::mat4(1.0f), m_camRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotYMat = glm::rotate(glm::mat4(1.0f), m_camRot.y, glm::vec3(0.0f, 1.0f, 0.0f));

	m_view = rotXMat * rotYMat * transMat;
}

glm::vec3* FreeCamera::GetCamPosPtr()
{
	return &m_camPos;
}