#include "Engine.h"
#include "API/OpenGL/OpenGLBackend.h"

void Engine::Run()
{
	OpenGLBackend::Init(800, 800);

	while (!OpenGLBackend::WindowShouldClose())
	{
		OpenGLBackend::Update();
		OpenGLBackend::SwapBuffers();
	}

	OpenGLBackend::Terminate();
}