#include <glm/gtc/type_ptr.hpp>
#include "RenderingItem.hpp"
#include "../Shader/Material/PhongMaterial.hpp"

RenderingItem::RenderingItem()
	:m_material(PhongMaterial()), m_vbo(0U), m_vao(0U), m_translation(glm::vec3()), m_rotation(glm::vec3()), m_scale(glm::vec3()), m_translationMat(1.0f), m_rotationXMat(1.0f), m_rotationYMat(1.0f), m_rotationZMat(1.0f), m_scaleMat(1.0f)
{}

void RenderingItem::Render() const
{
	m_material.Use();
}

void RenderingItem::SetTranslation(const float& x, const float& y, const float& z)
{
	m_translation.x = x;
	m_translation.y = y;
	m_translation.z = z;

	m_translationMat = glm::translate(glm::mat4(1.0f), m_translation);
}

void RenderingItem::SetRotationX(const float& angle)
{
	m_rotation.x = angle;

	m_rotationXMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void RenderingItem::SetRotationY(const float& angle)
{
	m_rotation.y = angle;

	m_rotationYMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void RenderingItem::SetRotationZ(const float& angle)
{
	m_rotation.z = angle;

	m_rotationZMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void RenderingItem::SetScale(const float& x, const float& y, const float& z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;

	m_scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
}

PhongMaterial& RenderingItem::GetMaterial()
{
	return m_material;
}

void RenderingItem::SetMaterial(const PhongMaterial& material)
{
	m_material = material;
}

RenderingItem::~RenderingItem()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}