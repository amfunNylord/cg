#include "pch.h"
#include "Window.h"
#include "DirectLight.h"

namespace
{
// Угол обзора по вертикали
constexpr double FIELD_OF_VIEW = 60 * M_PI / 180.0;
// Размер стороны кубооктаэдра
constexpr double CUBOCTAHEDRON_SIZE = 1;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 10;

// Ортонормируем матрицу 4*4 (это должна быть аффинная матрица)
glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m) // Ортонормализация означает приведение базиса в пространстве к ортонормированному базису, в котором все базисные векторы (столбцы или строки матрицы) имеют единичную длину и ортогональны друг другу.
{
	// Извлекаем подматрицу 3*3 из матрицы m и ортонормируем её
	const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	// Заменяем 3 столбца исходной матрицы
	return {
		glm::dvec4{ normalizedMatrix[0], 0.0 },
		glm::dvec4{ normalizedMatrix[1], 0.0 },
		glm::dvec4{ normalizedMatrix[2], 0.0 },
		m[3]
	};
}

} // namespace

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_cuboctahedron(CUBOCTAHEDRON_SIZE)
{
	m_cuboctahedron.SetSideColor(CuboctahedronSide::FRONT_SQUARE_FACE, { 1, 0, 0, 1});
	m_cuboctahedron.SetSideColor(CuboctahedronSide::BACK_SQUARE_FACE, { 0, 1, 0, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::RIGHT_SQUARE_FACE, { 0, 0, 1, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::LEFT_SQUARE_FACE, { 1, 1, 0, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::UPPER_SQUARE_FACE, { 1, 0, 1, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::BOTTOM_SQUARE_FACE, { 0, 1, 1, 1 });

	m_cuboctahedron.SetSideColor(CuboctahedronSide::RIGHT_UPPER_FRONT_TRIANGULAR_FACE, { 1, 0.5, 0, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::LEFT_UPPER_FRONT_TRIANGULAR_FACE, { 0.5, 0, 1, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::LEFT_BOTTOM_FRONT_TRIANGULAR_FACE, { 0.5, 0.5, 0.5, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::RIGHT_BOTTOM_FRONT_TRIANGULAR_FACE, { 0.2, 0.6, 0.9, 1 });

	m_cuboctahedron.SetSideColor(CuboctahedronSide::RIGHT_UPPER_BACK_TRIANGULAR_FACE, { 0, 0, 0, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::LEFT_UPPER_BACK_TRIANGULAR_FACE, { 0.5, 0.5, 1, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::LEFT_BOTTOM_BACK_TRIANGULAR_FACE, { 0.7, 0.2, 0.8, 1 });
	m_cuboctahedron.SetSideColor(CuboctahedronSide::RIGHT_BOTTOM_BACK_TRIANGULAR_FACE, { 0.4, 0.8, 0.2, 1 });

	m_cuboctahedron.SetSpecularColor({ 1, 1, 1, 1 });
	m_cuboctahedron.SetShininess(4.0f);
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
		const auto windowSize = GetFramebufferSize();

		const auto mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

// Вращаем камеру вокруг начала координат
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
	glViewport(0, 0, width, height);	//  используется для установки прямоугольной области вывода в окне отрисовки. Она определяет, какие координаты изображения будут отображаться в каких пикселях окна.

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);	// создает матрицу проекции, которая преобразует координаты вершин объектов из пространства мира в пространство камеры с учетом перспективы
	glLoadMatrixd(&proj[0][0]);	// используется для загрузки матрицы в стек матриц OpenGL
	glMatrixMode(GL_MODELVIEW);	// используется для установки текущей матрицы для дальнейших операций над матрицами.
}

void Window::OnRunStart()
{
	glEnable(GL_LIGHTING);	// включаем освещение
	glEnable(GL_LIGHT0);	// включаем источник света

	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);		
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);	

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);

	// Направление на источник света (совпадает с позицией наблюдателя)
	DirectLight light{ { 0.0f, 0.0f, 1.0f } };
	light.SetDiffuseIntensity({ 0.5f, 0.5f, 0.5f, 1.0f });	//  используется для установки интенсивности диффузного (рассеянного) освещения для конкретного источника света
	light.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });	
	light.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });		 
	light.Apply(GL_LIGHT0);	
}

void Window::Draw(int width, int height)
{
	glClearColor(1, 1, 1, 1);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	SetupCameraMatrix();

	m_cuboctahedron.Draw();
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
