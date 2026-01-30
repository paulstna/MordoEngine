#pragma once
#include <glad/glad.h>
#include <vector>
#include <random>
#include "../../Camera/Camera.h"
#include "Cube.h"

class CubeRenderer {
private:
	GLuint vao, vbo, ebo;
	std::vector<Cube> cubes;
	glm::vec3 cameraPosition = glm::vec3{ 0.0f,0.0f,-5.0f };
	void AddRandomCube();
	void HandleInputs(float deltaTime);
	Camera camera;
	std::string defaultTextureID;
	std::string defaultShaderID;
	std::mt19937 gen;
public:
	CubeRenderer();
	~CubeRenderer();
	void Update(float deltaTime);
	void Render();
};