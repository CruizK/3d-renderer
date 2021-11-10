#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer()
  : m_RendererID(0)
{

}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Create(u32* data, u32 size)
{
  glGenBuffers(1, &m_RendererID);
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}