#include <stb/stb_image.h>
#include "PhongMaterial.hpp"
#include <iostream>

PhongMaterial::PhongMaterial(Texture diffuse, Texture specular, Texture emissive)
	:m_diffuseTexture(Texture(diffuse)), m_specularTexture(Texture(specular)), m_emissiveTexture(Texture(emissive))
{
}

PhongMaterial::PhongMaterial(const PhongMaterial& other)
	:m_diffuseTexture(other.m_diffuseTexture), m_specularTexture(other.m_specularTexture), m_emissiveTexture(other.m_emissiveTexture)
{
}

void PhongMaterial::Use() const
{
	glActiveTexture(GL_TEXTURE0);
	m_diffuseTexture.Use();
	glActiveTexture(GL_TEXTURE1);
	m_specularTexture.Use();
	glActiveTexture(GL_TEXTURE2);
	m_emissiveTexture.Use();
}

void PhongMaterial::SetTextures(Texture diffuse, Texture specular, Texture emissive)
{
	m_diffuseTexture = diffuse;
	m_specularTexture = specular;
	m_emissiveTexture = emissive;
}

PhongMaterial& PhongMaterial::operator = (const PhongMaterial& other)
{
	m_diffuseTexture = other.m_diffuseTexture;
	m_specularTexture = other.m_specularTexture;
	m_emissiveTexture = other.m_emissiveTexture;

	return *this;
}

PhongMaterial::~PhongMaterial()
{
}