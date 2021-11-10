#include "MainScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	m_Shader.CreateFromFile("res/shaders/base.shader");

	float verticies[] = {
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		0.0f, 0.5f, 0
	};

	m_VertexBuffer.Create(verticies, sizeof(verticies));

	m_Layout.PushFloat(3); // X, Y, Z

	m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);
}

void MainScene::Update(float dt)
{

}

void MainScene::Draw()
{
	m_Shader.Use();
	m_VertexArray.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
