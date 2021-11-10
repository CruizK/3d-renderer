#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	void Run();

private:
	GLFWwindow *m_Window;
};
