#include "CubePointLightRenderer.h"

CubePointLightRenderer::CubePointLightRenderer()
{
	CreateGLState();
	PopulateBuffers();
	glBindVertexArray(0);
}


void CubePointLightRenderer::CreateGLState()
{
	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

	const GLsizei stride = 6 * sizeof(float);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
}

void CubePointLightRenderer::PopulateBuffers()
{
	static const float vertices[] = {
		// positions          // normals
		// Back face
		-0.5f,-0.5f,-0.5f,   0.0f, 0.0f,-1.0f,
		 0.5f,-0.5f,-0.5f,   0.0f, 0.0f,-1.0f,
		 0.5f, 0.5f,-0.5f,   0.0f, 0.0f,-1.0f,
		 0.5f, 0.5f,-0.5f,   0.0f, 0.0f,-1.0f,
		-0.5f, 0.5f,-0.5f,   0.0f, 0.0f,-1.0f,
		-0.5f,-0.5f,-0.5f,   0.0f, 0.0f,-1.0f,
		// Front face
		-0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		 0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		// Left face
		-0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,
		// Right face
		 0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f, 0.5f,-0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f,-0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,
		 // Bottom face
		 -0.5f,-0.5f,-0.5f,   0.0f,-1.0f, 0.0f,
		  0.5f,-0.5f,-0.5f,   0.0f,-1.0f, 0.0f,
		  0.5f,-0.5f, 0.5f,   0.0f,-1.0f, 0.0f,
		  0.5f,-0.5f, 0.5f,   0.0f,-1.0f, 0.0f,
		 -0.5f,-0.5f, 0.5f,   0.0f,-1.0f, 0.0f,
		 -0.5f,-0.5f,-0.5f,   0.0f,-1.0f, 0.0f,
		 // Top face
		 -0.5f, 0.5f,-0.5f,   0.0f, 1.0f, 0.0f,
		  0.5f, 0.5f,-0.5f,   0.0f, 1.0f, 0.0f,
		  0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
		  0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
		 -0.5f, 0.5f,-0.5f,   0.0f, 1.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}


void CubePointLightRenderer::Render()
{
	glBindVertexArray(m_Vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

CubePointLightRenderer::~CubePointLightRenderer()
{
	glDeleteBuffers(1, &m_Vbo);
	glDeleteVertexArrays(1, &m_Vao);
}