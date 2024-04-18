#pragma once

#include "TexturedCube.h"
#include "TexturedRectangle.h"
#include "TexturedTriangle.h"

class Cottage
{
public:
	Cottage();

	void Draw() const;

	void SetWallTexture(Texture const& texture);
	void SetWindowTexture(Texture const& texture);
	void SetDoorTextures(Texture const& doorTop);
	void SetGarageDoorTexture(Texture const& texture);
	void SetRoofTexture(Texture const& texture);

private:
	TexturedCube m_section1;
	TexturedCube m_section2;
	TexturedCube m_section3;

	TexturedRectangle m_window1;
	TexturedRectangle m_window2;

	TexturedRectangle m_door;

	TexturedRectangle m_garageDoor;

	TexturedRectangle m_roofFront;
	TexturedRectangle m_roofBack;

	TexturedTriangle m_roofLeft;
	TexturedTriangle m_roofRight;
};
