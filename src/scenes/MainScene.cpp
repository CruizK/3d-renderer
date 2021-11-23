#include "MainScene.h"
#include "core/Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

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
	m_Texture.LoadFromFile("../res/textures/wood.png");
	m_ContainerTexture.LoadFromFile("../res/textures/white.png");
	m_Camera = PerspectiveCamera(m_Window);

	m_SphereMesh.LoadOBJ("../res/models/sphere.obj");
	m_PlaneMesh.LoadOBJ("../res/models/plane.obj");
	m_MonkeyMesh.LoadOBJ("../res/models/monkey.obj");

	Reset();
}

void MainScene::Reset()
{
	m_Material.Ambient = glm::vec3(1.0f);
	m_Material.DiffuseTexture = &m_ContainerTexture;
	m_Material.Specular = glm::vec3(0.2f);
	m_Material.Shininess = 32.0f;
	m_Material.MShader = &m_Shader;

	m_GroundMaterial.Ambient = glm::vec3(1.0f);
	m_GroundMaterial.DiffuseTexture = &m_Texture;
	m_GroundMaterial.Specular = glm::vec3(0.2f);
	m_GroundMaterial.Shininess = 32.0f;
	m_GroundMaterial.MShader = &m_Shader;

	m_Light.Position = glm::vec3(-3.0f, 2.0f, 0.0f);
	m_LightModel.SetPosition(m_Light.Position);

	m_Light.Ambient = glm::vec3(0.5f);
	m_Light.Diffuse = glm::vec3(0.7f);
	m_Light.Specular = glm::vec3(1.0f);

	m_Light.Constant = 1.0f;
	m_Light.Linear = 0.9f;
	m_Light.Quadratic = 0.032f;



	m_PlaneModel.SetMesh(m_PlaneMesh);

	m_PlaneModel.SetPosition(glm::vec3(0, -0.5f, 0.0f));
	m_PlaneModel.SetScale(glm::vec3(10, 1.0f, 10));

	m_SpherePos = glm::vec3(0, 3.0f, 0);
	m_SphereModel.SetPosition(m_SpherePos);

	m_Acceleration = glm::vec3(0);
	m_Velocity = glm::vec3(0);

	m_SphereModel.SetMesh(m_SphereMesh);
	m_LightModel.SetMesh(m_SphereMesh);

	m_SphereModel.SetColor(glm::vec3(0.5f, 0.5f, 0.7f));

	m_MonkeyModel.SetMesh(m_MonkeyMesh);
	m_MonkeyModel.SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));

	m_LightModel.SetScale(glm::vec3(0.2f));
	m_LightModel.SetColor(glm::vec3(1.0f));

	m_Acceleration.y = -9.8f;

	m_Friction = 0.7f;

	m_CanBounce = false;
}

void MainScene::Update(float dt)
{
	if (dt >= 1.0f / 60.0f) return;

	m_Camera.Update(dt);

	
	float sphereRadius = 1.0f;
	float sphereBottom = m_SpherePos.y - sphereRadius;
	float planeTop = -0.5f; // Position + scale

	if (m_CanBounce) {
		m_Velocity += m_Acceleration * dt;

		if (sphereBottom <= planeTop)
		{
			m_Velocity.y = -m_Velocity.y * m_Friction;

			// Make it so that the sphere is not inside the plane
			m_SpherePos.y = planeTop + sphereRadius;

			// If negligible velocity, stop bounce
			if (abs(m_Velocity.y) <= 0.25f) {
				m_CanBounce = false;
			}
		}

		m_SpherePos += m_Velocity * dt;
		m_SphereModel.SetPosition(m_SpherePos);
	}

	if(Input::GetKeyDown(GLFW_KEY_A))
	{
		float rot = m_MonkeyModel.GetRotation();
		rot += 2.0f;
		m_MonkeyModel.SetRotation(rot);
	}
	else if(Input::GetKeyDown(GLFW_KEY_S))
	{
		float rot = m_MonkeyModel.GetRotation();
		rot -= 2.0f;
		m_MonkeyModel.SetRotation(rot);	
	}
}

void MainScene::OnClick(const glm::vec2& mousePos)
{
	// This is supposed to move the model to the camera, but that's not really possible due to
	// Mouse being 2d and having no real way to move it in the third dimension so frig it
	// Normalized Device Coordinates
	float x = 2.0f * mousePos.x / 800.0f - 1.0f;
	float y = 2.0f * mousePos.y / 600.0f - 1.0f;
	CORE_TRACE("{0}, {1}", x , -y);

	glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);

	glm::vec4 ray_eye = glm::inverse(m_Camera.GetProjectionMatrix()) * clipCoords;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
	
	glm::vec4 ray_wor = glm::inverse(m_Camera.GetViewMatrix()) * ray_eye;

	glm::vec4 worldPoint = ray_wor;
	glm::vec4 normalizedWorldPoint = glm::normalize(worldPoint);
	CORE_TRACE("{0}, {1}, {2}, {3}", worldPoint.x, worldPoint.y, worldPoint.z, worldPoint.w);
	//CORE_TRACE("{0}, {1}, {2}, {3}", normalizedWorldPoint.x, normalizedWorldPoint.y, normalizedWorldPoint.z, normalizedWorldPoint.w);

	//float z = m_MonkeyModel.GetPosition().z;
	//m_MonkeyModel.SetPosition(glm::vec3(worldPoint.x, worldPoint.y, z));
}

void MainScene::OnKey(int key, int scancode, int action, int mods)
{
	m_Camera.OnKey(key, scancode, action, mods);

	if(key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		m_CanBounce = true;
	}
	else if(key ==GLFW_KEY_R && action == GLFW_PRESS)
	{
		Reset();
	}
}

void MainScene::ImGui()
{
	ImGui::Begin("Debug Window");

	if (ImGui::CollapsingHeader("Model"))
	{
		ImGui::DragFloat3("Position", (float*)&m_SphereModel.GetPosition(), 0.1f);
		ImGui::DragFloat3("Velocity", (float*)&m_Velocity, 0.1f);
		ImGui::DragFloat3("Acceleration", (float*)&m_Acceleration, 0.1f);
		ImGui::InputFloat("Friction", &m_Friction, 0.05f, 0.1f, 1);
	}

	if (ImGui::CollapsingHeader("Camera"))
	{
		float pitch = m_Camera.GetPitch();
		float yaw = m_Camera.GetYaw();
		ImGui::DragFloat3("Position", (float*)&m_Camera.GetPosition(), 0.1f);
		ImGui::DragFloat("Pitch", &pitch, 0.1f);
		ImGui::DragFloat("Yaw", &yaw, 0.1f);
	}

	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::SliderFloat3("Ambient", (float*)&m_Material.Ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular", (float*)&m_Material.Specular, 0.0f, 1.0f);
		ImGui::InputFloat("Shininess", &m_Material.Shininess, 2, 8, 1);
	}

	if (ImGui::CollapsingHeader("Light"))
	{
		ImGui::DragFloat3("Position", (float*)&m_Light.Position, 0.1f);
		ImGui::Separator();
		ImGui::SliderFloat3("Ambient", (float*)&m_Light.Ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse", (float*)&m_Light.Diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular", (float*)&m_Light.Specular, 0.0f, 1.0f);
		ImGui::Separator();
		ImGui::Text("Attenuation");
		ImGui::SliderFloat("Linear", &m_Light.Linear, 0.0f, 1.0f);
		ImGui::SliderFloat("Quadratic", &m_Light.Quadratic, 0.0f, 1.0f);
	}

	ImGui::End();
}

void MainScene::Draw()
{
	m_LightModel.Draw(m_Camera, m_WhiteShader);	
	m_MonkeyModel.Draw(m_Camera, &m_Material, m_Light);
	m_SphereModel.Draw(m_Camera, &m_Material, m_Light);
	m_PlaneModel.Draw(m_Camera, &m_GroundMaterial, m_Light);
}
