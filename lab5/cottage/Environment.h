#pragma once

#include "TexturedRectangle.h"

class Environment
{
public:
	Environment();

	void Draw() const;

	void SetGroundTexture(Texture const& texture);

private:
	TexturedRectangle m_ground;
};
