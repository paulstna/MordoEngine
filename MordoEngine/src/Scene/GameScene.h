#pragma once
#include "Scene.h"
#include "../Camera/Camera.h"
#include "../Terrain/Terrain.h"
#include "../Renderer/Renderer.h"
#include "../Lighting/Sun.h"
#include <memory>

class GameScene : public Scene
{
private:
	Camera m_Camera;
	std::unique_ptr<terrain::Terrain> m_Terrain;
	std::unique_ptr<Renderer> m_Render;
	std::unique_ptr<Sun> m_Sun;

public:
	GameScene();
	void Render() override;
	void Update(float deltaTime) override;
	~GameScene() override;
};
