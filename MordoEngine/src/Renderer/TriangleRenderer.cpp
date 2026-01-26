#include "TriangleRenderer.h"
#include "../Input/Input.h"
#include <random>
#include <iostream>

TriangleRenderer::TriangleRenderer() : shader("triangle.vs", "triangle.fs"), flag(false) {

	// triangle base 
	float vertices[] = {
		 0.0f,  0.5f,
		-0.5f, -0.5f,
		 0.5f, -0.5f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// VBO base
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Instance VBO
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

	// position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Triangle), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	// size
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Triangle), (void*)(sizeof(glm::vec2)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	// color
	glVertexAttribPointer(
		3, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle),
		(void*)(sizeof(glm::vec2) + sizeof(float))
	);
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
}

TriangleRenderer::~TriangleRenderer() {
	triangles.clear();
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &instanceVBO);
	glDeleteVertexArrays(1, &vao);
}

void TriangleRenderer::AddRandomTriangle() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> pos(-1.0f, 1.0f);
	std::uniform_real_distribution<float> sizeDist(0.1f, 0.5f);
	std::uniform_real_distribution<float> color(0.0f, 1.0f);
	std::uniform_real_distribution<float> vel(-0.5f, 0.5f);

	triangles.push_back({
		{ pos(gen), pos(gen) },
		sizeDist(gen),
		{ color(gen), color(gen), color(gen) },
		{ vel(gen), vel(gen) }
		});

	flag = true;
}

void TriangleRenderer::Update(float deltaTime) {
	for (Triangle& t : triangles) {
		t.position += t.velocity * deltaTime;

		if (t.position.x > 1.0f || t.position.x < -1.0f)
			t.velocity.x *= -1.0f;

		if (t.position.y > 1.0f || t.position.y < -1.0f)
			t.velocity.y *= -1.0f;
	}

	flag = true;

	HandleInputs();
}

void TriangleRenderer::HandleInputs() {
	if (Input::KeyPressed(GLFW_KEY_SPACE))
	{
		AddRandomTriangle();
	}
}

void TriangleRenderer::Render() {
	shader.Use();
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

	if (flag) {
		glBufferData(
			GL_ARRAY_BUFFER,
			triangles.size() * sizeof(Triangle),
			triangles.data(),
			GL_DYNAMIC_DRAW
		);
		flag = false;
	}

	glDrawArraysInstanced(
		GL_TRIANGLES,
		0,
		3,
		triangles.size()
	);
}
