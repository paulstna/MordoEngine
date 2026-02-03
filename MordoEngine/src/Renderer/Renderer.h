#pragma once

class Renderer
{
public:
	virtual void Render() = 0;
	virtual ~Renderer() = default;
};
