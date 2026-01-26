#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Base path for shaders
std::filesystem::path Shader::basePath =
std::filesystem::current_path() / "res" / "shaders";

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexCode = readFile(basePath / vertexShaderPath);
	std::string fragmentCode = readFile(basePath / fragmentShaderPath);

	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	GLint success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM_LINKING_FAILED\n"
			<< infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::Use() const {
	glUseProgram(ID);
}

std::string Shader::readFile(const std::filesystem::path& path) {
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "ERROR::SHADER::FILE_NOT_FOUND\n"
			<< path << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

		std::cerr << "ERROR::SHADER::COMPILATION_FAILED ("
			<< (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
			<< ")\n" << infoLog << std::endl;
	}

	return shader;
}
