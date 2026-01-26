#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Triangle {
	glm::vec2 position;
	float size;
	glm::vec3 color;
	glm::vec2 velocity;
};
