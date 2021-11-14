#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer()
	: m_RendererID(0)
{
}

VertexBuffer::VertexBuffer(void *data, u32 size)
	: m_RendererID(0)
{
	Create(data, size);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Create(void *data, u32 size)
{
	glCreateBuffers(1, &m_RendererID);
	Bind();
	glNamedBufferStorage(m_RendererID, size, data, GL_DYNAMIC_STORAGE_BIT);
}

/*
* Will no longer work with NamedBufferStorage, because it is immutable
void VertexBuffer::UploadSubData(void *data, u32 size, u32 offset)
{
	// This won't work
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
*/

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}