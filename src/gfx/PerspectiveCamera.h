#pragma once

#include <glm/glm.hpp>
#include <core/Window.h>

class PerspectiveCamera
{
public:
	PerspectiveCamera();
	PerspectiveCamera(Window* window);
	~PerspectiveCamera();

	void Update(float dt);


	const glm::vec3& GetPosition() { return m_Position; }

	const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

private:
	void RecalcViewMatrix();

private:
	Window* m_Window;
	
	u32 m_PrevEnterState;

	float speed = 0.1f;
	float m_MouseSens = 0.1f;

	float m_Pitch = 0.0f;
	float m_Yaw = 90.0f;

	glm::vec2 m_LastMousePos = glm::vec2(800/2, 600/2);

	glm::vec3 m_Direction = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_Position;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
};