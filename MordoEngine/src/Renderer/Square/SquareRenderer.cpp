#include "SquareRenderer.h"
#include "../../Input/Input.h"
#include "../../Core/Managers/Manager.h"
#include "../../Core/Texture/Texture.h"
#include "../../Core/Shader/Shader.h"
#include <iostream>

SquareRenderer::SquareRenderer() : gen(std::random_device{}()) {

	defaultShaderID = "basic";
	defaultTextureID = "bricks";
	// base triangle // texcoords
	float vertices[] = {
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f   // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,                     // first triangle
		1, 2, 3                      // second triangle
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// VBO base
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// indices
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SquareRenderer::~SquareRenderer() {
	squares.clear();
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void SquareRenderer::AddRandomSquare() {
	std::uniform_real_distribution<float> pos(-1.0f, 1.0f);
	std::uniform_real_distribution<float> sizeDist(0.1f, 0.5f);
	std::uniform_real_distribution<float> color(0.0f, 1.0f);
	std::uniform_real_distribution<float> vel(-0.5f, 0.5f);

	squares.push_back({
		glm::vec3(pos(gen), pos(gen), 0.0f),
		sizeDist(gen),
		glm::vec3(color(gen), color(gen), color(gen)),
		glm::vec3(vel(gen), vel(gen), 0.0f)
		});
}

void SquareRenderer::Update(float deltaTime) {
	for (Square& triangle : squares) {
		triangle.Update(deltaTime);
	}
	HandleInputs();
}

void SquareRenderer::HandleInputs() {
	if (Input::KeyPressed(GLFW_KEY_SPACE))
	{
		AddRandomSquare();
	}
}

void SquareRenderer::Render() {
	Manager<Shader>::Get(defaultShaderID).Use();

	glBindVertexArray(vao);
	Manager<Texture>::Get(defaultTextureID).Use();
	for (Square& square : squares) {
		square.Render(Manager<Shader>::Get(defaultShaderID));
	}
	glBindVertexArray(0);
}
