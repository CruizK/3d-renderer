#pragma once

#include <core/Core.h>
#include <core/Window.h>
#include <glm/glm.hpp>

class Input
{
public:
	static void Init(Window* window);

	static bool GetKeyDown(u32 key);
	static bool GetLeftMouseClicked();
	static glm::vec2 GetMousePos();

private:
	static GLFWwindow* m_Window;
};