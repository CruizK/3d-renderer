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
	void OnKey(int key, int scancode, int action, int mods);

	const glm::vec3& GetPosition() { return m_Position; }
	const glm::vec3& GetDirection() { return m_Direction; }
	float GetPitch() { return m_Pitch; }
	float GetYaw() { return m_Yaw; }


	const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

private:
	void RecalcViewMatrix();

private:
	Window* m_Window;
	
	u32 m_PrevEnterState;

	float speed = 0.1f;
	float m_MouseSens = 0.1f;

	float m_Pitch = -23.3f;
	float m_Yaw = -99.6f;

	glm::vec2 m_LastMousePos = glm::vec2(1280/2, 720/2);

	glm::vec3 m_Direction = glm::vec3(0.676f, -0.327f, 0.660f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_Position;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
};