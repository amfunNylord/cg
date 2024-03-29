#include "pch.h"
#include "BaseWindow.h"

BaseWindow::BaseWindow(int w, int h, const char* title)
	: m_window{ MakeWindow(w, h, title) }
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}

	glfwSetWindowUserPointer(m_window, this); // пользовательские данные 

	glfwSetWindowSizeCallback(m_window,			
		[](GLFWwindow* window, int width, int height) {
			GetBaseWindow(window)->OnResize(width, height);
		}); // обратный вызов при resize

	glfwSetMouseButtonCallback(m_window,		
		[](GLFWwindow* window, int button, int action, int mods) {
			GetBaseWindow(window)->OnMouseButton(button, action, mods);
		}); // обратный вызов при нажатии клавиши

	glfwSetCursorPosCallback(m_window,			
		[](GLFWwindow* window, double x, double y) {
			GetBaseWindow(window)->OnMouseMove(x, y);
		}); // обратный вызов при движении мыши
}

BaseWindow::~BaseWindow()
{
	glfwDestroyWindow(m_window);
}

glm::ivec2 BaseWindow::GetFramebufferSize() const 
{
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h); // предоставляет размеры framebuffer - изображение отображаемое на экране
	return { w, h };
}

void BaseWindow::Run()
{
	glfwMakeContextCurrent(m_window);	// устанавливаем контекст для данного окна
	OnRunStart();

	{
		auto size = GetFramebufferSize();
		OnResize(size.x, size.y);
	}

	while (!glfwWindowShouldClose(m_window))
	{
		auto size = GetFramebufferSize();
		Draw(size.x, size.y);
		glFinish(); //  гарантирует, что все предыдущие команды OpenGL будут выполнены до продолжения выполнения программы
		glfwSwapBuffers(m_window);	// обеспечивает плавную анимацию и избегает неприятного мерцания, пока мы видим содержимое одного буфера, происходит рендеринг в другом
		glfwPollEvents();	// приложению реагировать на пользовательский ввод, перемещение мыши, изменения размера окна и другие события, обеспечивая плавную и отзывчивую работу интерфейса пользователя.
	}
	OnRunEnd();
}

glm::dvec2 BaseWindow::GetCursorPos() const
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return { x, y };
}

BaseWindow* BaseWindow::GetBaseWindow(GLFWwindow* window)
{
	return reinterpret_cast<BaseWindow*>(glfwGetWindowUserPointer(window));	//  позволяет интерпретировать биты одного типа данных как биты другого типа данных преобразовать указатель на базовый класс в указатель на производный класс или наоборот
}

GLFWwindow* BaseWindow::MakeWindow(int w, int h, const char* title)
{
	glfwWindowHint(GLFW_DEPTH_BITS, 24);	// указываем что глубина буфера должна быть 24 бита
	return glfwCreateWindow(w, h, title, nullptr, nullptr);
}
