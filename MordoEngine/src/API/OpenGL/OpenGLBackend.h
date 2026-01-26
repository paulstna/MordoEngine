#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLBackend
{
public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void Update();
	static void Terminate();
	static void Init(int width, int height);
	static GLFWwindow* GetGLFWwindow();
	static bool WindowShouldClose();
	static void CloseWindow();
	static void SwapBuffers();

private:
	OpenGLBackend();
	static GLFWwindow* window;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};