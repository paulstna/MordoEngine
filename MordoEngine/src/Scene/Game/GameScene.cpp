#include "GameScene.h"
#include "../../Core/Managers/Manager.h"
#include "../../Core/Shader/Shader.h"
#include "../../Input/Input.h"
#include "../../Renderer/SkyBoxRenderer.h"

GameScene::GameScene(std::shared_ptr<terrain::Terrain> terrain, std::shared_ptr<Camera> camera, std::shared_ptr<Renderer> renderer)
	: Scene("terrain"), m_Terrain(terrain), m_Camera(camera), m_Renderer(renderer) , m_LightSystem( std::make_unique<LightSystem>() )
{
	m_CameraController = std::make_unique<GameCameraController>(m_Camera);
	m_SkyBoxRenderer = std::make_unique<SkyBoxRenderer>(
		Manager<Shader>::Get("skyBox")
	);
}

void GameScene::OnEntry()
{
	m_CameraController->TouchTerrain(*m_Terrain);
}

void GameScene::Update(float deltaTime)
{
	float velocity = 100.0f * m_Terrain->GetWorldScale() * deltaTime;
	m_CameraController->Update(deltaTime, velocity, *m_Terrain);
    m_LightSystem->Update(deltaTime);
}

void GameScene::Render()
{
    glm::mat4 projection = m_Camera->GetProjectionMatrix();
    glm::mat4 view = m_Camera->GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 cameraPos = m_Camera->GetPosition();

    Shader& terrainShader = Manager<Shader>::Get("terrain");
    m_LightSystem->Render(terrainShader, cameraPos, &projection, &view, &model);
    m_Renderer->Render(cameraPos, &view, &projection, &model);
    m_SkyBoxRenderer->Render(&view, &projection, nullptr);
}

GameScene::~GameScene()
{

}