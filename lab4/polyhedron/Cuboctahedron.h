#pragma once

enum class CuboctahedronSide
{
	FRONT_SQUARE_FACE,
	BACK_SQUARE_FACE,
	RIGHT_SQUARE_FACE,
	LEFT_SQUARE_FACE,
	UPPER_SQUARE_FACE,
	BOTTOM_SQUARE_FACE,
	RIGHT_UPPER_FRONT_TRIANGULAR_FACE,
	LEFT_UPPER_FRONT_TRIANGULAR_FACE,
	LEFT_BOTTOM_FRONT_TRIANGULAR_FACE,
	RIGHT_BOTTOM_FRONT_TRIANGULAR_FACE,
	RIGHT_UPPER_BACK_TRIANGULAR_FACE,
	LEFT_UPPER_BACK_TRIANGULAR_FACE,
	LEFT_BOTTOM_BACK_TRIANGULAR_FACE,
	RIGHT_BOTTOM_BACK_TRIANGULAR_FACE,
};

class Cuboctahedron
{
public:
	explicit Cuboctahedron(float size = 1);
	void Draw() const;

	void SetSideColor(CuboctahedronSide side, const glm::vec4& color);
	/*void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);*/

private:
	float m_size;
	glm::vec4 m_sideColors[14];
	/*glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;*/
};
