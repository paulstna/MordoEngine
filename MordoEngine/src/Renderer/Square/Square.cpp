#include "Square.h"
#include "../../Core/Texture/Texture.h"
#include "../../Core/Managers/Manager.h"

Square::Square(glm::vec3 position, float size, glm::vec3 color, glm::vec3 velocity)
	: position(position), size(size), color(color), velocity(velocity)
{
	textureID = "bricks";
}

void Square::Update(float deltaTime) {
	// Update Square
}

void Square::Render(const Shader& shader) {
	shader.setVec3("iPos", position);
	shader.setFloat("iSize", size);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::Render(const Shader& shader, const std::string& defaultTextureID) {
	if (textureID != defaultTextureID) {
		Manager<Texture>::Get(textureID).Use();
	}
	Render(shader);
}