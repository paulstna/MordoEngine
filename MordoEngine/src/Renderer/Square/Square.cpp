#include "Square.h"

Square::Square(glm::vec3 position, float size, glm::vec3 color, glm::vec3 velocity)
	: position(position), size(size), color(color), velocity(velocity)
{
	textureID = TextureManager::Load("res/textures/bricks.png");
}

void Square::Update(float deltaTime) {

}

void Square::Render(const Shader& shader) {
	shader.setVec3("iPos", position);
	shader.setFloat("iSize", size);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::Render(const Shader& shader, TextureID defaultTextureID) {
	if (textureID != defaultTextureID) {
		TextureManager::Get(textureID).Use();
	}
	Render(shader);
}