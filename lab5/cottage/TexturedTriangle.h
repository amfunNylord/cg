#pragma once

#include "Texture.h"

class TexturedTriangle
{
public:
	TexturedTriangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);

	void Draw() const;

	void SetTexture(Texture const& texture);
	void SetTextureScale(float scale);

private:
	glm::vec3 m_vertex1;
	glm::vec3 m_vertex2;
	glm::vec3 m_vertex3;

	float m_textureScale = 1;

	Texture m_texture;
};
