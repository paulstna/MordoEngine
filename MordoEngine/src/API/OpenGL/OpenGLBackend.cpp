#include "OpenGLBackend.h"
#include <iostream>

GLFWwindow* OpenGLBackend::window;
unsigned int OpenGLBackend::SCR_WIDTH = 800;
unsigned int OpenGLBackend::SCR_HEIGHT = 800;

void OpenGLBackend::Init(int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "V1", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
}

GLFWwindow* OpenGLBackend::GetGLFWwindow()
{
	if (!window)
		return nullptr;

	return window;
}


void OpenGLBackend::Update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool OpenGLBackend::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}
void OpenGLBackend::SwapBuffers()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void OpenGLBackend::Terminate()
{
	glfwTerminate();
}

void OpenGLBackend::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}