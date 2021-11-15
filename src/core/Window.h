#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	void Run();

	GLFWwindow* GetRawPtr() { return m_Window; }

private:
	float lastFrame = 0.0f;
	GLFWwindow* m_Window;
};
