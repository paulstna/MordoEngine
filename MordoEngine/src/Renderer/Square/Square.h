#pragma once
#include <glm/glm.hpp>
#include "../../Core/Texture/TextureManager.h"
#include "../../Core/Shader/Shader.h"

class Square {
public:
	void Update(float deltaTime);
	void Render(const Shader& shader);
	void Render(const Shader& shader, TextureID defaultTextureID);
	Square(glm::vec3 position, float size, glm::vec3 color, glm::vec3 velocity);
	TextureID textureID;
	glm::vec3 getPosition() const { return position; }
private:
	glm::vec3 position;
	float size;
	glm::vec3 color;
	glm::vec3 velocity;
};