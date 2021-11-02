#include "Window.h"
#include "Log.h"
#include <glad/glad.h>
#include <iostream>



void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLuint severity, GLsizei length, const char* message, const void* userParam)
{
  CORE_ERROR("[OpenGL Error]: {0}", message);
}

Window::Window():
  _window(nullptr)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); Mac omega

  _window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
  if (_window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glViewport(0, 0, 800, 600);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);
}

Window::~Window()
{

}

void Window::Run()
{
  while (!glfwWindowShouldClose(_window))
  {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwPollEvents();
    glfwSwapBuffers(_window);
  }

  glfwTerminate();
}

