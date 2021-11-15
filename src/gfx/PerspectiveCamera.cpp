#include "PerspectiveCamera.h"
#include <core/Input.h>
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera():
	m_ProjectionMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0))
{
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
	: m_ProjectionMatrix(glm::perspective(fov, aspectRatio, near, far)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0))
{
	m_Position = glm::vec3(1.0f, 1.0f, -5.0f);
	RecalcViewMatrix();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::Update(float dt)
{
	speed = 2.5f * dt;

	if (Input::GetKeyDown(GLFW_KEY_W))
	{
		m_Position += speed * m_Direction;
	}
	if (Input::GetKeyDown(GLFW_KEY_A))
	{
		m_Position += speed * -glm::normalize(glm::cross(m_Direction, m_Up));
	}
	if (Input::GetKeyDown(GLFW_KEY_S))
	{
		m_Position += speed * -m_Direction;
	}
	if (Input::GetKeyDown(GLFW_KEY_D))
	{
		m_Position += speed * glm::normalize(glm::cross(m_Direction, m_Up));
	}
	if (Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		m_Position += speed * -m_Up;
	}
	if (Input::GetKeyDown(GLFW_KEY_SPACE))
	{
		m_Position += speed * m_Up;
	}

	glm::vec2 mousePos = Input::GetMousePos();

	float xOffset = mousePos.x - m_LastMousePos.x;
	float yOffset = m_LastMousePos.y - mousePos.y;

	xOffset *= m_MouseSens;
	yOffset *= m_MouseSens;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	m_LastMousePos = mousePos;

	glm::vec3 dir;
	dir.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	dir.y = sin(glm::radians(m_Pitch));
	dir.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Direction = glm::normalize(dir);

	RecalcViewMatrix();
}

void PerspectiveCamera::RecalcViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}
