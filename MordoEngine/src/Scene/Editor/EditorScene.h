#pragma once
#include "../Scene.h"
#include "../../Terrain/Terrain.h"
#include "../../Renderer/Geomipmapping.h"
#include "../../Camera/Camera.h"
#include "../../Renderer/AreaSelectorRenderer.h"
#include <memory>

class EditorScene : public Scene
{
private:
	std::shared_ptr<terrain::Terrain> m_Terrain;
	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<Renderer> m_Renderer;
	std::unique_ptr<AreaSelectorRenderer> m_TerrainSelector;

public:
	EditorScene(std::shared_ptr<terrain::Terrain> terrain, std::shared_ptr<Camera> camera, std::shared_ptr<Renderer> renderer);
	void Render() override;
	void Update(float deltaTime) override;
	~EditorScene() override;
};
