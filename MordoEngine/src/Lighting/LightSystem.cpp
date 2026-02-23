#include "LightSystem.h"
#include "./PointLight/PointLightData.h"
#include "./DirLight/DirLightData.h"
#include "../Core/Managers/Manager.h"

LightSystem::LightSystem() : m_DirLight(std::make_unique<DirLight>(0.9f))
{
	m_PointLights.push_back(PointLight(glm::vec3(928.f, 400.0f, 928.f)));
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
	m_PointLights[0].Render(lightCubeShader, projection, view, nullptr);

	shader.Use();
	shader.SetVec3("viewPos", cameraPos);

	const DirLightData& dirLight = m_DirLight->GetData();
	shader.SetVec3("dirLight.direction", dirLight.direction);
	shader.SetVec3("dirLight.ambient", dirLight.ambient);
	shader.SetVec3("dirLight.diffuse", dirLight.diffuse);

	const PointLightData& pointLight = m_PointLights[0].GetData();
	shader.SetVec3("pointLight.position", pointLight.position);
	shader.SetVec3("pointLight.ambient", pointLight.ambient);
	shader.SetVec3("pointLight.diffuse", pointLight.diffuse);
	shader.SetVec3("pointLight.specular", pointLight.specular);
	shader.SetFloat("pointLight.constant", pointLight.constant);
	shader.SetFloat("pointLight.linear", pointLight.linear);
	shader.SetFloat("pointLight.quadratic", pointLight.quadratic);
}

LightSystem::~LightSystem()
{
	m_PointLights.clear();
}