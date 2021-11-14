#pragma once

#include "Scene.h"
#include <gfx/Shader.h>
#include <gfx/buffers/VertexArray.h>
#include <gfx/buffers/IndexBuffer.h>
#include <gfx/Texture2D.h>
#include <gfx/PerspectiveCamera.h>

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;

private:
	Shader m_Shader;
	Texture2D m_Texture;
	PerspectiveCamera m_Camera;
	VertexBuffer m_VertexBuffer;
	VertexArray m_VertexArray;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IndexBuffer;
};