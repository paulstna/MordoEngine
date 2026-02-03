#include "GameScene.h"
#include "../Terrain/HeightmapTerrain.h"
#include "../API/OpenGL/OpenGLBackend.h"
#include "../Renderer/TriangleRenderer.h"
#include "../Core/Managers/Manager.h"
#include "../Core/Shader/Shader.h"
#include "../Input/Input.h"

GameScene::GameScene() : Scene("terrain"),
						m_Terrain(std::make_unique<HeightMapTerrain>("res/maps/heightmap.raw")),
						m_Camera(Camera(glm::vec3{ 0.0f, 50.0f, .0f },
								OpenGLBackend::SCR_WIDTH,
								OpenGLBackend::SCR_HEIGHT)
)
{
	m_Terrain->SetHeightScale(120.0f);
	m_Render = std::make_unique<TriangleRenderer>(*m_Terrain);
	Input::DisableCursor();
}

void GameScene::Update(float deltaTime)
{
	glm::vec3 newCameraPosition = m_Camera.GetPosition();
	float velocity = 25.0f * deltaTime;

	if (Input::KeyDown(GLFW_KEY_W)) {
		newCameraPosition += m_Camera.GetForward() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_A)) {
		newCameraPosition -= m_Camera.GetRight() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_S)) {
		newCameraPosition -= m_Camera.GetForward() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_D)) {
		newCameraPosition += m_Camera.GetRight() * velocity;
	}

	if (newCameraPosition != m_Camera.GetPosition()) {
		m_Camera.SetPosition(newCameraPosition);
	}
	m_Camera.ProcessMouseMovement(Input::MouseDeltaX(), Input::MouseDeltaY());
}

void GameScene::Render()
{
	Shader& shader = Manager<Shader>::Get(p_ShaderID);
	shader.Use();
	glm::mat4 projection = m_Camera.GetProjectionMatrix();
	glm::mat4 view = m_Camera.GetViewMatrix();
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", view);
	shader.SetFloat("heightScale", m_Terrain->GetHeightScale());
	m_Render->Render();
}

GameScene::~GameScene() 
{
	m_Terrain->UnloadHeightMap();
}