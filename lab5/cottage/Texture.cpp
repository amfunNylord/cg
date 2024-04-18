#include "Texture.h"

Texture::Texture(GLuint texture)
	: m_texture(texture)
{
}

void Texture::Delete() noexcept
{
	if (m_texture)
	{
		glDeleteTextures(1, &m_texture);
	}
}

void Texture::Bind() const
{
	if (m_texture)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
}
