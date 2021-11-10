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
	glGenBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::UploadSubData(void *data, u32 size, u32 offset)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}