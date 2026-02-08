#include "Sun.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Sun::Sun(float daySpeed) : m_DaySpeed(daySpeed) {}

void Sun::Update(float deltaTime)
{
	m_TimeOfDay += m_DaySpeed * deltaTime;


	if (m_TimeOfDay > glm::two_pi<float>()) {
		m_TimeOfDay -= glm::two_pi<float>();
	}
}
glm::vec3 Sun::GetReverseLightDirection()
{
	float x = 0.0f;
	float y = sin(m_TimeOfDay);  
	float z = cos(m_TimeOfDay);  

	return glm::normalize(glm::vec3(x, y, z));
}

glm::vec3 Sun::GetLightDirection()
{
	return -GetLightDirection();
}