#pragma once
#include <glad/glad.h>
#include <fstream>
#include <glm/mat4x4.hpp>
#include "../RenderingItem.hpp"

class OBJ : public RenderingItem
{
private:
	struct Info
	{
		unsigned int  positionsCount;
		unsigned int  uvsCount;
		unsigned int  normalsCount;
		unsigned int  verticesCount;
		unsigned int  facesCount;
		unsigned int* arr_verticesPerFace;
		Info();
		~Info();
	};
	Info m_info;
private:
	void LoadInfo(std::ifstream& file);
	void LoadPositions(std::ifstream& file, GLfloat* positions);
	void LoadNormals(std::ifstream& file, GLfloat* normals);
	void LoadUVs(std::ifstream& file, GLfloat* uvs);
	void LoadBuffers(std::ifstream& file, GLfloat* data);
public:
	OBJ(const char* filepath = nullptr);
	void Load(const char* filepath);
	void Render() const override;
};