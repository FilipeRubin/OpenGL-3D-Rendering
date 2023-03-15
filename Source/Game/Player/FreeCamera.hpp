#pragma once
#include <glm/glm.hpp>
#include "PlayerBase.hpp"

class FreeCamera : public PlayerBase
{
private:
	glm::mat4& m_view;
	glm::vec3& m_camPos;
	glm::vec3  m_camRot;
	double     m_lastX, m_lastY;
public:
	FreeCamera(GLFWwindow* pWindow, glm::mat4& view, glm::vec3& camPos);
	void Process() override;
	glm::vec3* GetCamPosPtr();
};