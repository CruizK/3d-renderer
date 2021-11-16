#pragma once

#include "Scene.h"
#include <gfx/Shader.h>
#include <gfx/buffers/VertexArray.h>
#include <gfx/buffers/IndexBuffer.h>
#include <gfx/Texture2D.h>
#include <gfx/PerspectiveCamera.h>
#include <gfx/Model.h>
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
	Model m_Model;
	Window* m_Window;
	Shader m_Shader;
	Shader m_WhiteShader;
	Texture2D m_Texture;
	PerspectiveCamera m_Camera;
	VertexBuffer m_VertexBuffer;
	VertexArray m_VertexArray;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IndexBuffer;
};