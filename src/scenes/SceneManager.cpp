#include "SceneManager.h"

Scene* SceneManager::m_Scene = nullptr;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::ChangeScene(Scene* scene)
{
	if(m_Scene != nullptr)
		delete m_Scene;
	m_Scene = scene;
	m_Scene->Init();
}

void SceneManager::Update(float dt)
{
	if(m_Scene != nullptr)
		m_Scene->Update(dt);
}

void SceneManager::ImGui()
{
	if(m_Scene != nullptr)
		m_Scene->ImGui();
}

void SceneManager::Draw()
{
	if(m_Scene != nullptr)
		m_Scene->Draw();
}