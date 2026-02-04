#pragma once
#include "../Core/Shader/Shader.h"

class Renderer
{
public:
	virtual void Render(const Shader& shader) = 0;
	virtual ~Renderer() = default;
};
