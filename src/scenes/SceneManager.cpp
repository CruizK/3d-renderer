#include "SceneManager.h"

Scene* SceneManager::s_Scene = nullptr;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	
}

void SceneManager::ChangeScene(Scene* scene)
{
	if(s_Scene != nullptr)
		delete s_Scene;
	s_Scene = scene;
	s_Scene->Init();
}

void SceneManager::Update(float dt)
{
	if(s_Scene != nullptr)
		s_Scene->Update(dt);
}

void SceneManager::OnKey(int key, int scancode, int action, int mods)
{
	if(s_Scene != nullptr)
		s_Scene->OnKey(key, scancode, action, mods);
}

void SceneManager::ImGui()
{
	if(s_Scene != nullptr)
		s_Scene->ImGui();
}

void SceneManager::Draw()
{
	if(s_Scene != nullptr)
		s_Scene->Draw();
}