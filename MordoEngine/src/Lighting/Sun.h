#pragma once
#include <glm/vec3.hpp>

class Sun 
{
public:
	Sun(float daySpeed);
	void Update(float deltaTime);
	glm::vec3 GetReverseLightDirection();
	glm::vec3 GetLightDirection();

private:
	float m_TimeOfDay = 0.0f; // 0 - 2pi 
	float m_DaySpeed = 0.1f;  
};
