#pragma once

#include "Scene.h"
#include <glm/glm.hpp>

class SceneManager
{
public:
	~SceneManager();

	static void ChangeScene(Scene* scene);

	static void Update(float dt);
	static void OnClick(const glm::vec2& mousePos);
	static void OnKey(int key, int scancode, int action, int mods);
	static void ImGui();
	static void Draw();

private:
	SceneManager();

	static Scene* s_Scene;
};