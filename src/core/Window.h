#pragma once

#include <core/Core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	void Run();

	u32 GetWidth() { return m_Width; }
	u32 GetHeight() { return m_Height; }

	void HideCursor() { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); m_CursorShown = false; }
	void ShowCursor() { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); m_CursorShown = true; }
	bool IsCursorShown() { return m_CursorShown; }

	GLFWwindow* GetRawPtr() { return m_Window; }

private:
	float lastFrame = 0.0f;
	u32 m_Width = 1280;
	u32 m_Height = 720;
	bool m_CursorShown = false;
	GLFWwindow* m_Window;
};
