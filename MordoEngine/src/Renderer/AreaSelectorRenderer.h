#pragma once
#include "Renderer.h"
#include "../Camera/Camera.h"
#include "../Terrain/Terrain.h"
#include <memory>
#include <string>

class AreaSelectorRenderer 
{
private:
	GLuint m_Vao;
	GLuint m_PosVbo;
	GLuint m_HeightVbo;
	glm::vec3 m_WorldPosition;
	std::string m_ShaderID;
	void CreateGLState();
	void PopulateBuffers(float radius, int segments);
	void InitVertices(std::vector<glm::vec2>& vertices, float radius, int segments);
public:
	AreaSelectorRenderer(float radius, int segments);
	void Render(const Camera& camera, int segments);
	void SetHeights(const std::vector<float>& heights, const glm::vec3& position);
	~AreaSelectorRenderer();
};
