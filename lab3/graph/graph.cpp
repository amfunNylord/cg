#include <GLFW/glfw3.h>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ CreateWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);
		while (!glfwWindowShouldClose(m_window))
		{
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(w, h);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

private:
	virtual void Draw(int width, int height) = 0;

	static GLFWwindow* CreateWindow(int w, int h, const char* title)
	{
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
	GLFWwindow* m_window;
};

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width, height);

		glBegin(GL_LINES);
		// ��������� x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.95f, 0.05f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.95f, -0.05f);

		float x0 = -1;
		float y0 = 0;

		for (int i = 0; i < 40; i++)
		{
			glVertex2f(x0, (float)(y0 + 0.05));
			glVertex2f(x0, (float)(y0 - 0.05));
			x0 += float(0.05);
		}

		// ��������� y
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(-0.05f, 0.95f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(0.05f, 0.95f);

		x0 = 0;
		y0 = -1;

		for (int i = 0; i < 40; i++)
		{
			glVertex2f((float)(x0 + 0.05), y0);
			glVertex2f((float)(x0 - 0.05), y0);
			y0 += float(0.05);
		}
		glEnd();

		// ���������� �������
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		for (int i = -2; i <= 3; i++)
		{
			x0 = (float)i;
			y0 = (float)(2 * pow(x0, 2)) - 3 * x0 - 8;
			glVertex2f(float(x0 * 0.05), float(y0 * 0.05));
		}
		glEnd();
	}
};

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 800, 600, "Graph" };
	window.Run();
}
