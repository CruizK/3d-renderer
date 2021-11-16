#pragma once

class Scene
{
public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void ImGui() = 0;
	virtual void Draw() = 0;
};