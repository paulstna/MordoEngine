#pragma once
#include <glad/glad.h>
#include <string>
#include <filesystem>

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();
	void Use() const;

private:
	static std::filesystem::path basePath;
	static std::string readFile(const std::filesystem::path& path);
	static GLuint compileShader(GLenum type, const std::string& source);
};
