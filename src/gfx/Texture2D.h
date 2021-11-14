#pragma once

#include "core/Core.h"

class Texture2D
{
public:
	Texture2D();
	~Texture2D();


	void LoadFromFile(const std::string& path);
	void LoadFromMemory(void* data, u32 width, u32 height, int channels);

	void Bind(u32 slot) const;
	void Unbind() const;

private:
	u32 m_RendererID, m_Width, m_Height;
};