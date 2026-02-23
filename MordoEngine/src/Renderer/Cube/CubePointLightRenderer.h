#pragma once
#include <glad/glad.h>

class CubePointLightRenderer
{
private:
	GLuint m_Vao;
	GLuint m_Vbo;
	void CreateGLState();
	void PopulateBuffers();

public:
	CubePointLightRenderer();
	void Render();
	~CubePointLightRenderer();
};