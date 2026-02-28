#include "LightSystem.h"
#include "./PointLight/PointLightData.h"
#include "./DirLight/DirLightData.h"
#include "../Core/Managers/Manager.h"

LightSystem::LightSystem() : m_DirLight(std::make_unique<DirLight>(0.9f))
{

}

void LightSystem::Update(float deltaTime)
{
	m_DirLight->Update(deltaTime);
}

void LightSystem::Render(const Shader& shader,
						 const glm::vec3& cameraPos,
						 const glm::mat4* projection,
						 const glm::mat4* view,
						 const glm::mat4* model)
{
	const Shader& lightCubeShader = Manager<Shader>::Get("light_cube");
	for (int i = 0; i < m_PointLights.size(); i++) {
		m_PointLights[i].Render(lightCubeShader, projection, view, nullptr);
	}

	shader.Use();
	shader.SetVec3("viewPos", cameraPos);

	const DirLightData& dirLight = m_DirLight->GetData();
	shader.SetVec3("dirLight.direction", dirLight.direction);
	shader.SetVec3("dirLight.ambient", dirLight.ambient);
	shader.SetVec3("dirLight.diffuse", dirLight.diffuse);

	shader.SetInt("numPointLights", m_PointLights.size());
	for (int i = 0; i < m_PointLights.size() && i < MAX_POINT_IGHTS; i++) {
		const PointLightData& pointLight = m_PointLights[i].GetData();
		shader.SetVec3("pointLights[" + std::to_string(i) + "].position", pointLight.position);
		shader.SetVec3("pointLights[" + std::to_string(i) + "].ambient", pointLight.ambient);
		shader.SetVec3("pointLights[" + std::to_string(i) + "].diffuse", pointLight.diffuse);
		shader.SetVec3("pointLights[" + std::to_string(i) + "].specular", pointLight.specular);
		shader.SetFloat("pointLights[" + std::to_string(i) + "].constant", pointLight.constant);
		shader.SetFloat("pointLights[" + std::to_string(i) + "].linear", pointLight.linear);
		shader.SetFloat("pointLights[" + std::to_string(i) + "].quadratic", pointLight.quadratic);
	}
}

void LightSystem::AddPointLight(PointLight&& pointLight)
{
	m_PointLights.push_back(std::move(pointLight));
}

LightSystem::~LightSystem()
{
	m_PointLights.clear();
}