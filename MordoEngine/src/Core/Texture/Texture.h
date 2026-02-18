#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>

class Texture {
public:
	GLuint ID;
	Texture(const std::string& texturePath);
	Texture(const std::string& filePath, const std::vector<std::string>& faces);
	void Use() const;
};
