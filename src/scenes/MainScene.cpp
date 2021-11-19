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


	m_Material.Ambient = glm::vec3(0.2f);
	m_Material.Diffuse = glm::vec3(0.5f);
	m_Material.Specular = glm::vec3(0.2f);
	m_Material.Shininess = 32.0f;
	m_Material.MShader = &m_Shader;

	m_SphereMesh.LoadOBJ("../res/models/sphere.obj");
	m_CubeMesh.LoadOBJ("../res/models/cube.obj");

	m_PlaneModel.SetMesh(m_CubeMesh);

	m_PlaneModel.SetPosition(glm::vec3(0, -3.0f, 0.0f));
	m_PlaneModel.SetScale(glm::vec3(10, 0.2f, 10));

	m_SphereModel.SetMesh(m_SphereMesh);
	m_LightModel.SetMesh(m_SphereMesh);

	m_SphereModel.SetColor(glm::vec3(0.5f, 0.5f, 0.7f));

	m_LightModel.SetScale(glm::vec3(0.2f));
	m_LightModel.SetColor(glm::vec3(1.0f));
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

	m_SphereModel.Draw(m_Camera, &m_Material, lightPos);
	//m_PlaneModel.Draw(m_Camera, &m_Material, lightPos);


	m_LightModel.SetPosition(lightPos);
	m_LightModel.Draw(m_Camera, m_WhiteShader, lightPos);
}
