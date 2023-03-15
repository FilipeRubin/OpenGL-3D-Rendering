#pragma once
#include <glad/glad.h>
#include "Texture.hpp"

class PhongMaterial
{
private:
	Texture m_diffuseTexture;
	Texture m_specularTexture;
	Texture m_emissiveTexture;
public:
	PhongMaterial(Texture diffuse = Texture(), Texture specular = Texture(), Texture emissive = Texture());
	PhongMaterial(const PhongMaterial& other);
	void Use() const;
	void SetTextures(Texture diffuse = Texture(), Texture specular = Texture(), Texture emissive = Texture());
	PhongMaterial& operator = (const PhongMaterial& other);
	~PhongMaterial();
};