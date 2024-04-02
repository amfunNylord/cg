#include "pch.h"
#include "Cuboctahedron.h"

Cuboctahedron::Cuboctahedron(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor(CuboctahedronSide::FRONT_SQUARE_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::BACK_SQUARE_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::RIGHT_SQUARE_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::LEFT_SQUARE_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::UPPER_SQUARE_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::BOTTOM_SQUARE_FACE, defaultColor);

	SetSideColor(CuboctahedronSide::RIGHT_UPPER_FRONT_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::LEFT_UPPER_FRONT_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::LEFT_BOTTOM_FRONT_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::RIGHT_BOTTOM_FRONT_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::RIGHT_UPPER_BACK_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::LEFT_UPPER_BACK_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::LEFT_BOTTOM_BACK_TRIANGULAR_FACE, defaultColor);
	SetSideColor(CuboctahedronSide::RIGHT_BOTTOM_BACK_TRIANGULAR_FACE, defaultColor);
}

void Cuboctahedron::Draw() const
{
	static constexpr float vertices[12][3] = {
		{ -1, -1, 0 }, // 0
		{ 0, -1, +1 }, // 1
		{ +1, -1, 0 }, // 2
		{ 0, -1, -1 }, // 3
		{ -1, 0, -1 }, // 4
		{ +1, 0, -1 }, // 5
		{ +1, +1, 0 }, // 6
		{ +1, 0, +1 }, // 7
		{ 0, +1, -1 }, // 8
		{ -1, +1, 0 }, // 9
		{ 0, +1, +1 }, // 10
		{ -1, 0, +1 }, // 11
	};

	static constexpr unsigned char triangularFaces[8][3] = {
		{ 11, 10, 9 }, // ����� ���� ���� ����
		{ 10, 7, 6 }, // ������ ���� ���� ����
		{ 0, 1, 11 }, // ����� ��� ���� ����
		{ 1, 2, 7 }, // ������ ��� ���� ����
		{ 4, 9, 8 }, // ����� ���� ������� ����
		{ 8, 6, 5 }, // ������ ���� ������� ����
		{ 0, 4, 3 }, // ����� ��� ������� ����
		{ 3, 5, 2 }, // ������ ��� ������� ����
	};

	static constexpr unsigned char squareFaces[6][4] = {
		{ 11, 1, 7, 10 }, // �������
		{ 4, 8, 5, 3 }, // ������
		{ 7, 2, 5, 6 }, // ������
		{ 0, 11, 9, 4 }, // �����
		{ 1, 0, 3, 2 }, // ������
		{ 10, 6, 8, 9 }, // �������
	};

	static size_t const triangularFaceCount = sizeof(triangularFaces) / sizeof(*triangularFaces);
	static size_t const squareFaceCount = sizeof(squareFaces) / sizeof(*squareFaces);

	glEnable(GL_COLOR_MATERIAL);
	// ���� ������� ����� ��������� ��������� � ������� ������ ���������
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	glScalef(m_size * 0.5f, m_size * 0.5f, m_size * 0.5f);

	glBegin(GL_TRIANGLES);
	{
		for (size_t face = 0; face < triangularFaceCount; ++face)
		{
			// ������������� ���� �����
			glColor4fv(glm::value_ptr(m_sideColors[face + 6]));

			const unsigned char* facePoints = triangularFaces[face];

			auto p0 = glm::make_vec3(vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(vertices[facePoints[2]]);

			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));

			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < squareFaceCount; ++face)
		{
			// ������������� ���� �����
			glColor4fv(glm::value_ptr(m_sideColors[face]));

			const unsigned char* facePoints = squareFaces[face];

			auto p0 = glm::make_vec3(vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(vertices[facePoints[2]]);
			auto p3 = glm::make_vec3(vertices[facePoints[3]]);

			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));

			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
			glVertex3fv(glm::value_ptr(p3));
		}
	}
	glEnd();
}

void Cuboctahedron::SetSideColor(CuboctahedronSide side, const glm::vec4& color)
{
	unsigned index = static_cast<unsigned>(side);
	m_sideColors[index] = color;
}

void Cuboctahedron::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void Cuboctahedron::SetShininess(float shininess)
{
	m_shininess = shininess;
}
