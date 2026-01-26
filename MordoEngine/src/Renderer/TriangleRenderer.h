#pragma once
#include <glad/glad.h>
#include "../Core/Shader/Shader.h"
#include "Triangle.h"
#include <vector>

class TriangleRenderer {
private:
	GLuint vao, vbo, instanceVBO;
	std::vector<Triangle> triangles;
	Shader shader;
	bool flag;
	void AddRandomTriangle();
	void HandleInputs();

public:
	TriangleRenderer();
	~TriangleRenderer();
	void Update(float deltaTime);
	void Render();
};
