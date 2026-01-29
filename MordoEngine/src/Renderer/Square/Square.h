#pragma once
#include <glm/glm.hpp>
#include "../../Core/Shader/Shader.h"

class Square {
public:
	void Update(float deltaTime);
	void Render(const Shader& shader);
	void Render(const Shader& shader, const std::string& defaultTextureID);
	Square(glm::vec3 position, float size, glm::vec3 color, glm::vec3 velocity);
	std::string textureID;
private:
	glm::vec3 position;
	float size;
	glm::vec3 color;
	glm::vec3 velocity;
};