#pragma once

#include "Scene.h"

class SceneManager
{
public:
	~SceneManager();

	static void ChangeScene(Scene* scene);

	static void Update(float dt);
	static void ImGui();
	static void Draw();

private:
	SceneManager();

	static Scene* m_Scene;
};