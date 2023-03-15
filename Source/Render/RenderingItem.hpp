#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "../Shader/Material/PhongMaterial.hpp"

class RenderingItem
{
protected:
	PhongMaterial m_material;
	GLuint m_vbo;
	GLuint m_vao;
	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_translationMat;
	glm::mat4 m_rotationXMat;
	glm::mat4 m_rotationYMat;
	glm::mat4 m_rotationZMat;
	glm::mat4 m_scaleMat;
public:
	RenderingItem();
	~RenderingItem();
	virtual void Render() const;
	void SetTranslation(const float& x, const float& y, const float& z);
	void SetRotationX(const float& angle);
	void SetRotationY(const float& angle);
	void SetRotationZ(const float& angle);
	void SetScale(const float& x, const float& y, const float& z);
	PhongMaterial& GetMaterial();
	void SetMaterial(const PhongMaterial& phongMaterial);

	friend class RenderingList;
};
