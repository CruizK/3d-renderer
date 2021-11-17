#include "PerspectiveCamera.h"
#include <core/Input.h>
#include <glm/gtc/matrix_transform.hpp>
#include <core/Log.h>

PerspectiveCamera::PerspectiveCamera():
	m_ProjectionMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0))
{
}

PerspectiveCamera::PerspectiveCamera(Window* window)
	: m_Window(window)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)((float)window->GetWidth() / (float)window->GetHeight()), 0.1f, 100.0f);
	m_ViewMatrix = glm::mat4(1.0f);
	m_Position = glm::vec3(1.0f, 1.0f, -5.0f);
	RecalcViewMatrix();

	prevEnterState = GLFW_RELEASE;
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


	u32 state = Input::GetKey(GLFW_KEY_ENTER);

	if (state == GLFW_RELEASE && prevEnterState == GLFW_PRESS)
	{
		if (m_Window->IsCursorShown())m_Window->HideCursor();
		else m_Window->ShowCursor();
	}

	prevEnterState = state;
	//CORE_TRACE(Input::GetKeyUp(GLFW_KEY_ENTER));

	glm::vec2 mousePos = Input::GetMousePos();
	if (!m_Window->IsCursorShown())
	{

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



		glm::vec3 dir;
		dir.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		dir.y = sin(glm::radians(m_Pitch));
		dir.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Direction = glm::normalize(dir);
	}
	m_LastMousePos = mousePos;
	RecalcViewMatrix();
}

void PerspectiveCamera::RecalcViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}
