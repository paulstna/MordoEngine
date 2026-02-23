#pragma once
#include "./PointLight/PointLight.h"
#include "./DirLight/DirLight.h"
#include "../Core/Shader/Shader.h"
#include <vector>
#include <memory>

class LightSystem
{
private:
	std::vector<PointLight> m_PointLights;
	std::unique_ptr<DirLight> m_DirLight;

public:
	LightSystem();
	void Update(float deltaTime);
	void Render(const Shader& shader, 
				const glm::vec3& cameraPos, 
				const glm::mat4* projection,
				const glm::mat4* view,
				const glm::mat4* model);
	~LightSystem();
};
