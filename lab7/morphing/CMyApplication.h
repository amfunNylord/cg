#pragma once

#include "../libgl/GLApplication.h"
#include "../libgl/Shaders.h"
#include "../libgl/AnimationController.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);
	~CMyApplication() = default;

protected:
	virtual void OnDisplay();
	virtual void OnInit();
	virtual void OnIdle();
	virtual void OnReshape(int width, int height);

private:
	void InitShaders();

private:
	CProgram m_program;
	CShader m_vertexShader;
	CAnimationController m_animationController;

	float m_phase = 0;
};