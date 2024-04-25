#include "Window.h"
#include "DirectLight.h"

namespace
{
constexpr double FIELD_OF_VIEW = 60 * M_PI / 180.0;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 20;

glm::dmat4x4 Orthonormalize(glm::dmat4x4 const& m)
{
	auto const normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	return {
		glm::dvec4{ normalizedMatrix[0], 0.0 },
		glm::dvec4{ normalizedMatrix[1], 0.0 },
		glm::dvec4{ normalizedMatrix[2], 0.0 },
		m[3]
	};
}
} // namespace

Window::Window(int w, int h, char const* title)
	: BaseWindow(w, h, title)
{
}

Window::~Window() noexcept
{
	m_groundTexture.Delete();

	m_wallTexture.Delete();
	m_windowTexture.Delete();
	m_door.Delete();
	m_garageDoorTexture.Delete();
	m_roofTexture.Delete();
}

void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		auto const windowSize = GetFramebufferSize();

		auto const mouseDelta = mousePos - m_mousePos;
		double const xAngle = mouseDelta.y * M_PI / windowSize.y;
		double const yAngle = mouseDelta.x * M_PI / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

// объяснить что такое ортонормированная матрица, как можно перемножить векторы
void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	// Извлекаем из 1 и 2 строки матрицы камеры направления осей вращения,
	// совпадающих с экранными осями X и Y.
	// Строго говоря, для этого надо извлекать столбцы их обратной матрицы камеры, но так как
	// матрица камеры ортонормированная, достаточно транспонировать её подматрицу 3*3
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

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	auto const proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		m_fogEnabled = !m_fogEnabled;
	}
}

void Window::OnRunStart()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	SetupLight();
	SetupTextures();
}

void Window::SetupLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	DirectLight light({ 0.0f, 0.0f, 1.0f });
	light.SetDiffuseIntensity({ 0.5f, 0.5f, 0.5f, 1.0f });
	light.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
	light.Apply(GL_LIGHT0);
}

void Window::SetupTextures()
{
	glEnable(GL_TEXTURE_2D);

	m_groundTexture = m_textureLoader.LoadTexture("Assets/grass.jpg");
	m_environment.SetGroundTexture(m_groundTexture);

	m_wallTexture = m_textureLoader.LoadTexture("Assets/wall.jpg");
	m_cottage.SetWallTexture(m_wallTexture);

	m_windowTexture = m_textureLoader.LoadTexture("Assets/window.jpg");
	m_cottage.SetWindowTexture(m_windowTexture);

	m_door = m_textureLoader.LoadTexture("Assets/door.jpg");
	m_cottage.SetDoorTextures(m_door);

	m_garageDoorTexture = m_textureLoader.LoadTexture("Assets/garageDoor.jpg");
	m_cottage.SetGarageDoorTexture(m_garageDoorTexture);

	m_roofTexture = m_textureLoader.LoadTexture("Assets/roof.jpg");
	m_cottage.SetRoofTexture(m_roofTexture);
}

void Window::Draw(int width, int height)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();
	SetupFog();

	m_environment.Draw();
	m_cottage.Draw();
}

void Window::SetupCameraMatrix() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}

void Window::SetupFog()
{
	if (m_fogEnabled)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		const float density = 0.15f;
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		GLfloat fogColor[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // Цвет тумана (серый)
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, density);

	}
	else
	{
		glDisable(GL_FOG);
	}
}
