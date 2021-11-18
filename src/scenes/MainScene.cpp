#include "MainScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>

MainScene::MainScene(Window* window):
	m_Window(window)
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{

	m_Shader.CreateFromFile("../res/shaders/lighting.shader");
	m_WhiteShader.CreateFromFile("../res/shaders/white.shader");
	m_Texture.LoadFromFile("../res/textures/container.jpg");
	m_Camera = PerspectiveCamera(m_Window);


	m_SphereMesh.LoadOBJ("../res/models/sphere.obj");

	m_SphereModel.SetMesh(m_SphereMesh);
	m_LightModel.SetMesh(m_SphereMesh);

	m_SphereModel.SetColor(glm::vec3(0.5f, 0.5f, 0.7f));

	m_LightModel.SetScale(glm::vec3(0.2f));
	m_LightModel.SetColor(glm::vec3(228.0f / 255, 151.0f / 255, 89.0f / 255));
}

void MainScene::Update(float dt)
{
	m_Camera.Update(dt);
}

void MainScene::ImGui()
{

}

void MainScene::Draw()
{
	glm::vec3 lightPos = glm::vec3(3.0f, 0.0f, 3.0f);
	lightPos = glm::rotateY(lightPos, (float)glfwGetTime() * glm::radians(25.0f));

	m_Shader.Use();
	m_Shader.SetVec3("lightPos", lightPos);
	m_Shader.SetVec3("viewPos", m_Camera.GetPosition());
	m_Shader.SetVec3("lightColor", m_LightModel.GetColor());

	m_SphereModel.Draw(m_Camera, m_Shader, lightPos);

	m_LightModel.SetPosition(lightPos);
	m_LightModel.Draw(m_Camera, m_WhiteShader, lightPos);
}
