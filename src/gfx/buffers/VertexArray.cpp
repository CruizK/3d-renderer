#include "VertexArray.h"
#include <glad/glad.h>

VertexArray::VertexArray()
  : m_RendererID(0), m_AttribIndex(0), m_AttribOffset(0)
{
  glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
  Bind();
  vb.Bind();

  const auto& elements = layout.GetElements();
  u32 offset = 0;
  for ( u32 i = 0; i < elements.size(); i++)
  {
    const auto& element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i,
      element.count,
      element.type,
      element.normalized,
      layout.GetStride(),
      (void*) offset);
    offset += element.size;
  }
}

void VertexArray::Bind() const
{
  glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
  glBindVertexArray(0);
}
