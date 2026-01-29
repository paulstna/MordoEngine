#pragma once
#include <glad/glad.h>
#include <vector>
#include <random>
#include "Square.h"

class SquareRenderer {
private:
	GLuint vao, vbo, ebo;
	std::vector<Square> squares;
	void AddRandomSquare();
	void HandleInputs();
	std::string defaultTextureID;
	std::string defaultShaderID;
	std::mt19937 gen;
public:
	SquareRenderer();
	~SquareRenderer();
	void Update(float deltaTime);
	void Render();
};