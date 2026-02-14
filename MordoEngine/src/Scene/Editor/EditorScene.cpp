#include "EditorScene.h"
#include "../../Core/Managers/Manager.h"
#include "../../Core/Shader/Shader.h"
#include "../../Input/Input.h"

EditorScene::EditorScene(std::shared_ptr<terrain::Terrain> terrain, std::shared_ptr<Camera> camera, std::shared_ptr<Renderer> renderer)
	: Scene("terrain"), m_Terrain(terrain), m_Camera(camera), m_Renderer(renderer)
{
	m_CameraController = std::make_unique<EditorCameraController>(m_Camera);
	m_EditorSystem = std::make_unique<EditorSystem>();
}


void EditorScene::Update(float deltaTime)
{
	float velocity = 100.0f * m_Terrain->GetWorldScale() * deltaTime;
	m_CameraController->Update(deltaTime, velocity);
	m_EditorSystem->Update(*m_Terrain, *m_Camera);
}

void EditorScene::Render()
{
	Shader& shader = Manager<Shader>::Get(p_ShaderID);
	shader.Use();

	glm::mat4 projection = m_Camera->GetProjectionMatrix();
	shader.SetMat4("projection", projection);

	glm::mat4 view = m_Camera->GetViewMatrix();
	shader.SetMat4("view", view);

	shader.SetVec3("reverseLightDir", glm::vec3(0.0f, 1.0f, 0.0f));

	m_Renderer->Render(shader, m_Camera->GetPosition());
	m_EditorSystem->Render(*m_Camera);
}

EditorScene::~EditorScene()
{
	//
}