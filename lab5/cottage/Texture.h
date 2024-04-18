#pragma once

#include "common_inc.h"

class Texture
{
public:
	Texture() = default;
	Texture(GLuint texture);

	void Delete() noexcept;
	void Bind() const;

private:
	GLuint m_texture = 0;
};
