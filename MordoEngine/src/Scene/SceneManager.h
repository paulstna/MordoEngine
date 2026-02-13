#pragma once
#include <memory>
#include <unordered_map>
#include "../Renderer/Renderer.h"
#include "../Terrain/Terrain.h"
#include "../Camera/Camera.h"
#include <string>
#include "Scene.h"

class SceneManager
{
private:
	std::shared_ptr<Camera> m_SharedCamera;
	std::shared_ptr<terrain::Terrain> m_SharedTerrain;
	std::shared_ptr<Renderer> m_SharedRenderer;

	std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
	Scene* m_ActiveScene;
	std::string m_ActiveSceneName;

public:
	SceneManager();

	void AddScene(const std::string& name, std::unique_ptr<Scene> scene);
	void RemoveScene(const std::string& name);

	Scene* GetActiveScene() const;
	void SetActiveScene(const std::string& name);

	Scene* GetScene(const std::string& name);

	void Update(float deltaTime);
	void Render();

	~SceneManager();
};