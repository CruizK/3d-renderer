#include "Input.h"

GLFWwindow* Input::m_Window = nullptr;

void Input::Init(Window* window)
{
	m_Window = window->GetRawPtr();
}

bool Input::GetKeyDown(u32 key)
{
	return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Input::GetLeftMouseClicked()
{
	return glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE;
}

glm::vec2 Input::GetMousePos()
{
	double x, y;
	glfwGetCursorPos(m_Window, &x, &y);
	return glm::vec2(x, y);
}