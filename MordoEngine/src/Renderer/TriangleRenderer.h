#pragma once
#include "Renderer.h"
#include "../Terrain/Terrain.h"
#include <glad/glad.h>

class TriangleRenderer : public Renderer
{
public:
	TriangleRenderer(const terrain::Terrain& terrain);
	void Render() override;
	~TriangleRenderer();
private:
	int m_Width;
	int m_Depth;
	GLuint m_Vao;
	GLuint m_Vbo;
	GLuint m_Ebo;
	void CreateTriangleList(const terrain::Terrain& terrain);
	void CreateGLState();
	void PopulateBuffers(const terrain::Terrain& terrain);
	void InitVertices(const terrain::Terrain& terrain, std::vector<terrain::Vertex>& vertices);
	void InitIndices(std::vector<unsigned int>& indices);
};
