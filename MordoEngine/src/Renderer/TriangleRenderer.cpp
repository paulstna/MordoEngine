#include "TriangleRenderer.h"
#include <cassert>

TriangleRenderer::TriangleRenderer(const terrain::Terrain& terrain)
{
	CreateTriangleList(terrain);
}

void TriangleRenderer::CreateTriangleList(const terrain::Terrain& terrain)
{
	m_Width = terrain.GetSize();
	m_Depth = terrain.GetSize();

	CreateGLState();
	PopulateBuffers(terrain);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TriangleRenderer::CreateGLState()
{
	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glGenBuffers(1, &m_Ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(terrain::Vertex), (const void*)(sizeof(float) * 0));
}

void TriangleRenderer::PopulateBuffers(const terrain::Terrain& terrain)
{
	std::vector<terrain::Vertex> vertices;
	vertices.resize(terrain.GetSize() * terrain.GetSize());

	std::vector<unsigned int> indices;
	int numQuads = (m_Width - 1) * (m_Depth - 1);
	indices.resize(numQuads * 6);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	InitVertices(terrain, vertices);
	InitIndices(indices);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

void TriangleRenderer::InitVertices(const terrain::Terrain& terrain, std::vector<terrain::Vertex>& vertices)
{
	int index = 0;
	for (int x = 0; x < m_Width; x++) {
		for (int z = 0; z < m_Depth; z++) {
			assert(index < vertices.size());
			vertices[index++].InitVertex(terrain, x, z);
		}
	}
}

void TriangleRenderer::InitIndices(std::vector<unsigned int>& indices)
{
	int index = 0;
	for (int x = 0; x < m_Width - 1; x++) {
		for (int z = 0; z < m_Depth - 1; z++) {
			unsigned int IndexBottomLeft = z * m_Width + x;
			unsigned int IndexTopLeft = (z + 1) * m_Width + x;
			unsigned int IndexTopRight = (z + 1) * m_Width + x + 1;
			unsigned int IndexBottomRight = z * m_Width + x + 1;

			assert(index < indices.size());
			indices[index++] = IndexBottomLeft;
			assert(index < indices.size());
			indices[index++] = IndexTopLeft;
			assert(index < indices.size());
			indices[index++] = IndexTopRight;

			assert(index < indices.size());
			indices[index++] = IndexBottomLeft;
			assert(index < indices.size());
			indices[index++] = IndexTopRight;
			assert(index < indices.size());
			indices[index++] = IndexBottomRight;
		}
	}
}

void TriangleRenderer::Render()
{
	glBindVertexArray(m_Vao);
	glDrawElements(GL_TRIANGLES, (m_Width - 1) * (m_Depth - 1) * 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

TriangleRenderer::~TriangleRenderer()
{
	glDeleteBuffers(1, &m_Vbo);
	glDeleteBuffers(1, &m_Ebo);
	glDeleteVertexArrays(1, &m_Vao);
}
