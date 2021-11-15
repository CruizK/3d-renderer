#include "Window.h"
#include "Log.h"
#include <glad/glad.h>
#include <iostream>
#include <gfx/buffers/VertexBuffer.h>
#include <gfx/buffers/VertexArray.h>
#include <gfx/Shader.h>
#include <scenes/SceneManager.h>
#include <scenes/MainScene.h>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLuint severity, GLsizei length, const char *message, const void *userParam)
{
	if (type == GL_DEBUG_TYPE_ERROR)
		CORE_ERROR("[OpenGL Error]: {0}", message);
	else
		CORE_TRACE("[OpenGL Debug]: {0}", message);
}

Window::Window() : m_Window(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); Mac omega

	m_Window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (m_Window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_Window);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, 800, 600);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glDebugMessageCallback(MessageCallback, 0);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
}

void Window::Run()
{
	SceneManager::ChangeScene(new MainScene(this));

	while (!glfwWindowShouldClose(m_Window))
	{
		float deltaTime = 0.0f;
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		SceneManager::Update(deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SceneManager::Draw();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	glfwTerminate();
}
