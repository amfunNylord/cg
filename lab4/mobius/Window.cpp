#include "pch.h"
#include "Window.h"
#include "MobiusStrip.h"

namespace
{

// ������������� ������� 4*4 (��� ������ ���� �������� �������)
glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
{
	// ��������� ���������� 3*3 �� ������� m � ������������� �
	const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	// �������� 3 ������� �������� �������
	return {
		glm::dvec4{ normalizedMatrix[0], 0.0 },
		glm::dvec4{ normalizedMatrix[1], 0.0 },
		glm::dvec4{ normalizedMatrix[2], 0.0 },
		m[3]
	};
}

} // namespace

void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_buttonPressed = (action & GLFW_PRESS) != 0;
	}
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_buttonPressed)
	{
		const auto windowSize = GetFramebufferSize();

		const auto mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

// ������� ������ ������ ������ ���������
void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	// ��������� �� 1 � 2 ������ ������� ������ ����������� ���� ��������,
	// ����������� � ��������� ����� X � Y.
	// ������ ������, ��� ����� ���� ��������� ������� �� �������� ������� ������, �� ��� ���
	// ������� ������ �����������������, ���������� ��������������� � ���������� 3*3
	const glm::dvec3 xAxis{
		m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
	};
	const glm::dvec3 yAxis{
		m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
	};
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

	m_cameraMatrix = Orthonormalize(m_cameraMatrix);
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	// ��������� ����������� ������ ���������� ������� ����
	double aspect = double(width) / double(height);

	// �������, ��� ������ ������� ������� ����� FRUSTUM_SIZE
	// (�� ���������� �� ������� ��������� ���������)
	double frustumHeight = FRUSTUM_SIZE;
	// ������ ������� ������� �������������� �������� ����������� ������ ����
	// (���� ���� - ���� ������� ��������� � ��������)
	double frustumWidth = frustumHeight * aspect;

	// ���� ������ ������� ������� ���������� ������, ��� FRUSTUM_SIZE,
	// �� ������������ ������� ������� �������
	if (frustumWidth < FRUSTUM_SIZE && (aspect != 0))
	{
		frustumWidth = FRUSTUM_SIZE;
		frustumHeight = frustumWidth / aspect;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-frustumWidth * 0.5, frustumWidth * 0.5,
		-frustumHeight * 0.5, frustumHeight * 0.5,
		FRUSTUM_SIZE * 0.5, FRUSTUM_SIZE * 20);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	glLineWidth(2);

	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
}

void Window::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();

	MobiusStrip mobiusStrip;
	mobiusStrip.Draw();
}

void Window::SetupProjectionMatrix(int width, int height)
{
	glViewport(0, 0, width, height);

	// ��������� ����������� ������ ���������� ������� ����
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto projMat = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 10.0);
	glLoadMatrixd(&projMat[0][0]);
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}