#pragma once
#include "PointLightData.h"
#include "../../Renderer/Cube/CubePointLightRenderer.h"
#include "../../Core/Shader/Shader.h"
#include <memory>

class PointLight
{
private:
	PointLightData m_Data;
	std::unique_ptr<CubePointLightRenderer> m_Renderer;

public:
	PointLight(const glm::vec3 position);
    PointLight(const PointLight&) = delete;
    PointLight& operator=(const PointLight&) = delete;

    PointLight(PointLight&& other) noexcept
        : m_Data(std::move(other.m_Data)),
        m_Renderer(std::move(other.m_Renderer))
    {
    }

    PointLight& operator=(PointLight&& other) noexcept
    {
        if (this != &other)
        {
            m_Data = std::move(other.m_Data);
            m_Renderer = std::move(other.m_Renderer);
        }
        return *this;
    }

	void Update(float deltaTime);
	void Render(const Shader& shader, 
				const glm::mat4* projection,
				const glm::mat4* view, 
				const glm::mat4* model);
	const PointLightData& GetData() const { return m_Data; }
};

