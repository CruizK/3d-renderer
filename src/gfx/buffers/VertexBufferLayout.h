#pragma once
#include "core/Core.h"
#include "core/Log.h"
#include <glad/glad.h>
#include <vector>

struct VertexBufferElement
{
	u32 type;
	u32 count;
	unsigned char normalized;
	u32 size;

	static u32 GetSizeOfType(u32 type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			CORE_ERROR("Vertex Buffer Element of type does not exist");
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	void PushFloat(u32 count);
	void PushUInt(u32 count);
	void PushUChar(u32 count);

	inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }
	inline u32 GetStride() const { return m_Stride; }

private:
	void Push(u32 type, u32 count, unsigned char normalized);

	std::vector<VertexBufferElement> m_Elements;
	u32 m_Stride;
};