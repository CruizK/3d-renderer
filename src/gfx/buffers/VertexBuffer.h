#pragma once
#include "core/Core.h"

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(void *data, u32 size);
	~VertexBuffer();

	void Create(void *data, u32 size);
	void UploadSubData(void *data, u32 size, u32 offset);

	void Bind() const;
	void Unbind() const;

private:
	u32 m_RendererID;
};