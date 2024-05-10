#include "../libgl/pch.h"
#include "CMyApplication.h"
#include "../libgl/ProgramLinker.h"
#include "Scene.h"
#include "../libgl/ShaderCompiler.h"
#include "../libgl/ShaderLoader.h"

namespace
{
constexpr float ANIMATION_PERIOD = 1.0f;
}

CMyApplication::CMyApplication(const char* title, int width, int height)
	: CGLApplication(title, width, height)
{
}

void CMyApplication::OnInit()
{
	InitShaders();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLint phaseLocation = m_program.GetUniformLocation("phase");
}

void CMyApplication::OnIdle()
{
	m_animationController.Tick();

	float delta = m_animationController.GetTimeDelta() * 0.0003f;
	m_phase += delta;

	if (m_phase > ANIMATION_PERIOD)
	{
		m_phase = std::fmodf(m_phase, ANIMATION_PERIOD);
	}
	PostRedisplay();
}

void CMyApplication::InitShaders()
{
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error("The OpenGL implementation does not support geometry shaders");
	}

	CShaderLoader loader;
	m_vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "shader.vsh");

	m_program.Create();
	m_program.AttachShader(m_vertexShader);

	CShaderCompiler compiler;
	compiler.CompileShader(m_vertexShader);
	compiler.CheckStatus();

	CProgramLinker linker;
	linker.LinkProgram(m_program);
	linker.CheckStatus();
}

void CMyApplication::OnDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);
	glUniform1f(m_program.GetUniformLocation("phase"), m_phase);

	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	Scene::Draw();
	glPopMatrix();

	glUseProgram(0);
}

void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height) * 0.7;
	gluOrtho2D(-aspectRatio, aspectRatio, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
}