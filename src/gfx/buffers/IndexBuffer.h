#pragma once
#include <core/Core.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void Create(u32 *data, u32 count);

	void Bind() const;
	void Unbind() const;

private:
	u32 m_RendererID;
};