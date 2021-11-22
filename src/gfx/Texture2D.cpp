#include "Texture2D.h"
#include <glad/glad.h>
#include <stb_image.h>
#include "core/Log.h"

Texture2D::Texture2D() :
	m_RendererID(0), m_Width(0), m_Height(0)
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture2D::LoadFromFile(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, channels = 0;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		LoadFromMemory(data, width, height, channels);
	}
	else 
	{
		CORE_ERROR("Could not load texture from: {0}", path);
	}

	stbi_image_free(data);
}

void Texture2D::LoadFromMemory(void* data, u32 width, u32 height, int channels)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	u32 internalFormat = 0, dataFormat = 0;

	CORE_ASSERT(channels == 3 || channels == 4, "Specified unsupported amount of channels");

	if (channels == 3)
	{
		internalFormat = GL_RGB;
		dataFormat = GL_RGB;
	}
	else if (channels == 4)
	{
		internalFormat = GL_RGBA;
		dataFormat = GL_RGBA;
	}

	CORE_TRACE("(Loading Texture) Width: {0} | Height {1} | Channels: {2}", width, height, channels);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	m_Width = width;
	m_Height = height;
}

void Texture2D::Bind(u32 slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
