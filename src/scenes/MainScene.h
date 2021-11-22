#pragma once

#include "Scene.h"
#include <gfx/Shader.h>
#include <gfx/buffers/VertexArray.h>
#include <gfx/buffers/IndexBuffer.h>
#include <gfx/Texture2D.h>
#include <gfx/PerspectiveCamera.h>
#include <gfx/Model.h>
#include <gfx/Material.h>
#include <gfx/Light.h>
#include <core/Window.h>

class MainScene : public Scene
{
public:
	MainScene(Window* window);
	~MainScene();

	void Init() override;
	void Reset();

	void Update(float dt) override;
	void OnKey(int key, int scancode, int action, int mods) override;
	void ImGui() override;
	void Draw() override;

private:
	glm::vec3 m_LightPos;
	Mesh m_SphereMesh;
	Mesh m_PlaneMesh;
	Mesh m_MonkeyMesh;

	Model m_MonkeyModel;
	Model m_PlaneModel;
	Model m_SphereModel;
	Model m_LightModel;

	Light m_Light;

	Material m_Material;
	Material m_GroundMaterial;

	glm::vec3 m_SpherePos;
	glm::vec3 m_Acceleration;
	glm::vec3 m_Velocity;
	float m_Friction;

	bool m_CanBounce;


	Window* m_Window;
	Shader m_Shader;
	Shader m_WhiteShader;
	Texture2D m_Texture;
	Texture2D m_ContainerTexture;
	PerspectiveCamera m_Camera;
};