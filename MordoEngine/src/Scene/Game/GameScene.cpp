#include "GameScene.h"
#include "../../Core/Managers/Manager.h"
#include "../../Core/Shader/Shader.h"
#include "../../Input/Input.h"

GameScene::GameScene(std::shared_ptr<terrain::Terrain> terrain, std::shared_ptr<Camera> camera, std::shared_ptr<Renderer> renderer) 
	: Scene("terrain"), m_Terrain(terrain) , m_Camera(camera) , m_Renderer(renderer) , m_Sun(std::make_unique<Sun>(0.9f))
{

}

void GameScene::Update(float deltaTime)
{
	m_Sun->Update(deltaTime);
	glm::vec3 newCameraPosition = m_Camera->GetPosition();
	float velocity = 100.0f * m_Terrain->GetWorldScale() * deltaTime;

	if (Input::KeyDown(GLFW_KEY_W)) {
		newCameraPosition += m_Camera->GetForward() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_A)) {
		newCameraPosition -= m_Camera->GetRight() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_S)) {
		newCameraPosition -= m_Camera->GetForward() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_D)) {
		newCameraPosition += m_Camera->GetRight() * velocity;
	}

	if (newCameraPosition != m_Camera->GetPosition()) {
		m_Camera->SetPosition(newCameraPosition);
	}
	m_Camera->ProcessMouseMovement(Input::MouseDeltaX(), Input::MouseDeltaY());
}

void GameScene::Render()
{
	Shader& shader = Manager<Shader>::Get(p_ShaderID);
	shader.Use();

	glm::mat4 projection = m_Camera->GetProjectionMatrix();
	shader.SetMat4("projection", projection);

	glm::mat4 view = m_Camera->GetViewMatrix();
	shader.SetMat4("view", view);

	shader.SetVec3("reverseLightDir", m_Sun->GetReverseLightDirection());
	m_Renderer->Render(shader, m_Camera->GetPosition());
}

GameScene::~GameScene()
{
	
}