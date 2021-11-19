#pragma once

#include "Scene.h"
#include <gfx/Shader.h>
#include <gfx/buffers/VertexArray.h>
#include <gfx/buffers/IndexBuffer.h>
#include <gfx/Texture2D.h>
#include <gfx/PerspectiveCamera.h>
#include <gfx/Model.h>
#include <gfx/Material.h>
#include <core/Window.h>

class MainScene : public Scene
{
public:
	MainScene(Window* window);
	~MainScene();

	void Init() override;
	void Update(float dt) override;
	void ImGui() override;
	void Draw() override;

private:
	glm::vec3 m_LightPos;
	Mesh m_SphereMesh;
	Mesh m_CubeMesh;

	Model m_PlaneModel;
	Model m_SphereModel;
	Model m_LightModel;

	Material m_Material;

	Window* m_Window;
	Shader m_Shader;
	Shader m_WhiteShader;
	Texture2D m_Texture;
	PerspectiveCamera m_Camera;
};