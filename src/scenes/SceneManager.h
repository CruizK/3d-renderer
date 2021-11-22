#pragma once

#include "Scene.h"

class SceneManager
{
public:
	~SceneManager();

	static void ChangeScene(Scene* scene);

	static void Update(float dt);
	static void OnKey(int key, int scancode, int action, int mods);
	static void ImGui();
	static void Draw();

private:
	SceneManager();

	static Scene* s_Scene;
};