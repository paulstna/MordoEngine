#pragma once
#include <glad/glad.h>
#include "../../Core/Texture/TextureManager.h"
#include "../../Core/Shader/Shader.h"
#include <vector>
#include "Square.h"
#include <random>

class SquareRenderer {
private:
	GLuint vao, vbo, ebo;
	std::vector<Square> squares;
	Shader shader;
	void AddRandomTriangle();
	void HandleInputs();
	TextureID defaultTextureID;
	std::mt19937 gen;
public:
	SquareRenderer();
	~SquareRenderer();
	void Update(float deltaTime);
	void Render();
};