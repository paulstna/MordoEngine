#include "EditorCameraController.h"
#include "../../../Input/Input.h"

EditorCameraController::EditorCameraController(std::weak_ptr<Camera> camera) : m_Camera(camera)
{

}

void EditorCameraController::Update(float deltaTime, float velocity)
{
	auto camera = m_Camera.lock();
	if (!camera) {
		return;
	}
	glm::vec3 newCameraPosition = camera->GetPosition();

	if (Input::KeyDown(GLFW_KEY_W)) {
		newCameraPosition += camera->GetForward() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_A)) {
		newCameraPosition -= camera->GetRight() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_S)) {
		newCameraPosition -= camera->GetForward() * velocity;
	}
	if (Input::KeyDown(GLFW_KEY_D)) {
		newCameraPosition += camera->GetRight() * velocity;
	}

	if (newCameraPosition != camera->GetPosition()) {
		camera->SetPosition(newCameraPosition);
	}
	camera->ProcessMouseMovement(Input::MouseDeltaX(), Input::MouseDeltaY());
}