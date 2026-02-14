#include "AreaSelectorRenderer.h"
#include "../Core/Managers/Manager.h"
#include "../Core/Shader/Shader.h"
#include <iostream>


AreaSelectorRenderer::AreaSelectorRenderer(float radius, int segments)
{
	m_ShaderID = "terrainSelector";
	CreateGLState();
	PopulateBuffers(radius, segments);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AreaSelectorRenderer::CreateGLState()
{
	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_PosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_PosVbo);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_HeightVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_HeightVbo);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
	glEnableVertexAttribArray(1);

}

void AreaSelectorRenderer::PopulateBuffers(float radius, int segments)
{
	std::vector<glm::vec2> verticesXZ;
	std::vector<float> heights(segments, 0.0f);

	InitVertices(verticesXZ, radius, segments);

	glBindBuffer(GL_ARRAY_BUFFER, m_PosVbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		verticesXZ.size() * sizeof(verticesXZ[0]),
		&verticesXZ[0],
		GL_STATIC_DRAW
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_HeightVbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		heights.size() * sizeof(heights[0]),
		&heights[0],
		GL_DYNAMIC_DRAW
	);
}

void AreaSelectorRenderer::InitVertices(std::vector<glm::vec2>& vertices, float radius, int segments)
{

	for (int i = 0; i < segments; ++i)
	{
		float angle = (float)i / segments * glm::two_pi<float>();

		vertices.push_back({
			glm::cos(angle) * radius,
			glm::sin(angle) * radius
			});
	}
}

void AreaSelectorRenderer::SetHeights(const std::vector<float>& heights, const glm::vec3& position)
{
	m_WorldPosition = position;
	glBindVertexArray(m_Vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_HeightVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, heights.size() * sizeof(float), heights.data());
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AreaSelectorRenderer::Render(const Camera& camera, int segments)
{
	Shader& shader = Manager<Shader>::Get(m_ShaderID);
	shader.Use();

	glm::mat4 projection = camera.GetProjectionMatrix();
	shader.SetMat4("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	shader.SetMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_WorldPosition);
	shader.SetMat4("model", model);

	glBindVertexArray(m_Vao);
	glLineWidth(10.0f);
	glDrawArrays(GL_LINE_LOOP, 0, segments);
	glBindVertexArray(0);
}

AreaSelectorRenderer::~AreaSelectorRenderer()
{
	glDeleteBuffers(1, &m_PosVbo);
	glDeleteBuffers(1, &m_HeightVbo);
	glDeleteVertexArrays(1, &m_Vao);
}