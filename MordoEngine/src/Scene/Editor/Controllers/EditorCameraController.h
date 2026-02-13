#pragma once
#include "../../../Input/Input.h"
#include "../../../Camera/Camera.h"
#include <memory>

class EditorCameraController
{
private:
	std::weak_ptr<Camera> m_Camera;

public:
	EditorCameraController(std::weak_ptr<Camera> camera);
	void Update(float deltaTime , float velocity);
};
