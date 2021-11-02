#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window
{
public:
  Window();
  ~Window();

  void Run();

private:
  GLFWwindow* _window;
};
